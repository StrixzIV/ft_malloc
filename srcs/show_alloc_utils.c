/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jikaewsi <strixz.self@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 00:35:30 by jikaewsi          #+#    #+#             */
/*   Updated: 2025/11/17 00:51:42 by jikaewsi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_malloc.h"

void put_unbr_fd(size_t nb, int fd) {

	if (nb >= 10) {
		put_unbr_fd(nb / 10, fd);
	}
	
    ft_putchar_fd((nb % 10) + '0', fd);

}

void put_hex_fd(size_t nb, int fd) {

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

void put_hex_byte(unsigned char byte, int fd) {
	
    char c = (byte >> 4);

	if (c < 10)
		ft_putchar_fd(c + '0', fd);
	else
		ft_putchar_fd(c - 10 + 'A', fd);
	
	c = (byte & 0x0F);

	if (c < 10)
		ft_putchar_fd(c + '0', fd);
	else
		ft_putchar_fd(c - 10 + 'A', fd);
}

/**
 * @brief Prints a hexadecimal dump of memory content
 * @param addr Starting address
 * @param size Number of bytes to dump
 */
void print_hex_dump(void *addr, size_t size) {

	unsigned char *ptr = (unsigned char *)addr;
	size_t display_size = (size > HEXDUMP_SIZE) ? HEXDUMP_SIZE : size;
	
	ft_putstr_fd("Hexdump (first ", 1);
	put_unbr_fd(display_size, 1);
	ft_putstr_fd(" bytes):\n", 1);
	
	for (size_t i = 0; i < display_size; i++) {

		if (i % 16 == 0) {
			put_hex_fd((size_t)(ptr + i), 1);
			ft_putstr_fd(": ", 1);
		}
		
		put_hex_byte(ptr[i], 1);
		ft_putchar_fd(' ', 1);
		
		if ((i + 1) % 16 == 0) {

			ft_putstr_fd(" | ", 1);
			
            for (size_t j = i - 15; j <= i; j++) {
				if (ptr[j] >= 32 && ptr[j] <= 126)
					ft_putchar_fd(ptr[j], 1);
				else
					ft_putchar_fd('.', 1);
			}
			
            ft_putchar_fd('\n', 1);
		
        }
	}
	
	if (display_size % 16 != 0) {
		
        size_t remaining = 16 - (display_size % 16);
		
        for (size_t i = 0; i < remaining; i++) {
			ft_putstr_fd("   ", 1);
		}

		ft_putstr_fd(" | ", 1);
        size_t start = (display_size / 16) * 16;
		
        for (size_t j = start; j < display_size; j++) {

			if (ptr[j] >= 32 && ptr[j] <= 126)
				ft_putchar_fd(ptr[j], 1);
			
            else
				ft_putchar_fd('.', 1);
		
        }
		
        ft_putchar_fd('\n', 1);
	
    }
	
	if (size > HEXDUMP_SIZE) {
		ft_putstr_fd("... (", 1);
		put_unbr_fd(size - HEXDUMP_SIZE, 1);
		ft_putstr_fd(" bytes truncated)\n", 1);
	}

}

void sort(void **head, size_t count) {

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
