/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jikaewsi <strixz.self@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 02:25:04 by jikaewsi          #+#    #+#             */
/*   Updated: 2025/11/04 02:25:04 by jikaewsi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_malloc.h"

static void put_unbr_fd(size_t nb, int fd) {

	if (nb >= 10) {
		put_unbr_fd(nb / 10, fd);
	}

	ft_putchar_fd((nb % 10) + '0', fd);

}

static void put_hex_fd(size_t nb, int fd) {

	if (nb >= 16) {
		put_hex_fd(nb / 16, fd);
	}

	char c = (nb % 16);
	
	if (c < 10) {
		ft_putchar_fd(c + '0', fd);
	}

	else {
		ft_putchar_fd(c - 10 + 'A', fd);
	}

}

static void sort(void **head, size_t count) {

	if (head == NULL || count < 2) {
		return;
	}
	
	for (size_t i = 0; i < count - 1; i++) {
		for (size_t j = i + 1; j < count; j++) {
			if (head[i] > head[j]) {
				void * temp = head[i];
				head[i] = head[j];
				head[j] = temp;
			}
		}
	}
}

static void print_block(t_block_metadata * head, size_t * total) {

	size_t used_block_count = 0;
	t_block_metadata * current = head;

	while (current != NULL) {
		used_block_count++;
		current = current->next;
	}

	t_block_metadata ** ptr_vector = allocate(NULL, used_block_count * sizeof(t_block_metadata *));

	if (ptr_vector == NULL)
		return;

	current = head;
	size_t index = 0;

	while (current != NULL)	{
		ptr_vector[index++] = current;
		current = current->next;
	}

	// Sort buffer by address
	sort((void **)ptr_vector, used_block_count);

	for (size_t i = 0; i < used_block_count; i++) {

		current = ptr_vector[i];
		void *buffer_addr = (void *)((char *)current + aligned_header_size());
		
		ft_putstr_fd("0x", 1);
		put_hex_fd((size_t)buffer_addr, 1);
		ft_putstr_fd(" - 0x", 1);
		put_hex_fd((size_t)buffer_addr + current->block_size, 1);
		ft_putstr_fd(" : ", 1);
		put_unbr_fd(current->block_size, 1);
		ft_putstr_fd(" bytes\n", 1);

		*total += current->block_size;

	}

}

static void print_zone(t_zone_metadata * head, char * name, size_t * total) {
	
	size_t used_block_count = 0;
	t_zone_metadata * current = head;
	
	while (current != NULL) {
		used_block_count++;
		current = current->next;
	}

	t_zone_metadata ** ptr_vector = allocate(NULL, used_block_count * sizeof(t_zone_metadata *));
	if (ptr_vector == NULL)
		return;

	current = head;
	size_t index = 0;
	while (current != NULL) {
		ptr_vector[index++] = current;
		current = current->next;
	}

	// Sort buffer by address
	sort((void **)ptr_vector, used_block_count);

	for (size_t i = 0; i < used_block_count; i++) {

		current = ptr_vector[i];
		
		if (current->used_blocks == NULL) {
			continue;
		}
		
		ft_putstr_fd(name, 1);
		ft_putstr_fd(" : 0x", 1);
		put_hex_fd((size_t)current, 1);
		ft_putstr_fd("\n", 1);

		print_block(current->used_blocks, total);

	}

}

/**
 * @brief Displays the state of allocated memory, sorted by address.
 */
void show_alloc_mem() {

	pthread_mutex_lock(&g_tracker.alloc_lock);

	size_t total = 0;

	if (g_tracker.tiny_chunk) {
		print_zone(g_tracker.tiny_chunk, "TINY", &total);
	}

	if (g_tracker.small_chunk) {
		print_zone(g_tracker.small_chunk, "SMALL", &total);
	}

	if (g_tracker.used_large_chunk) {
		ft_putstr_fd("LARGE :\n", 1);
		print_block(g_tracker.used_large_chunk, &total);
	}

	ft_putstr_fd("Total allocated: ", 1);
	put_unbr_fd(total, 1);
	ft_putstr_fd(" bytes\n", 1);
	
	pthread_mutex_unlock(&g_tracker.alloc_lock);

}
