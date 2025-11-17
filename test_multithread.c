/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_multithread.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jikaewsi <jikaewsi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 14:58:11 by jikaewsi          #+#    #+#             */
/*   Updated: 2025/11/17 15:45:10 by jikaewsi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/ft_malloc.h"
#include <string.h>
#include <stdio.h>
#include <pthread.h>

#define N_THREADS 8
#define N_ALLOCS_PER_THREAD 1000

typedef struct s_thread_data {
	int thread_id;
	int n_allocs;
	int success;
} t_thread_data;

void *thread_allocate_free(void *arg)
{
	t_thread_data *data = (t_thread_data *)arg;
	void *ptrs[N_ALLOCS_PER_THREAD];
	
	// Allocate
	for (int i = 0; i < data->n_allocs; i++) {
		size_t size = (data->thread_id * 37 + i * 13) % 2000 + 1;
		ptrs[i] = malloc(size);
		if (!ptrs[i]) {
			printf("Thread %d: malloc failed at iteration %d\n", data->thread_id, i);
			data->success = 0;
			return NULL;
		}
		// Write some data
		memset(ptrs[i], (char)(data->thread_id + i), size);
	}
	
	// Free half
	for (int i = 0; i < data->n_allocs / 2; i++) {
		free(ptrs[i]);
	}
	
	// Reallocate
	for (int i = data->n_allocs / 2; i < data->n_allocs; i++) {
		size_t new_size = (data->thread_id * 41 + i * 17) % 3000 + 1;
		ptrs[i] = realloc(ptrs[i], new_size);
		if (!ptrs[i]) {
			printf("Thread %d: realloc failed at iteration %d\n", data->thread_id, i);
			data->success = 0;
			return NULL;
		}
	}
	
	// Free remaining
	for (int i = data->n_allocs / 2; i < data->n_allocs; i++) {
		free(ptrs[i]);
	}
	
	data->success = 1;
	return NULL;
}

void *thread_stress_test(void *arg)
{
	t_thread_data *data = (t_thread_data *)arg;
	
	for (int i = 0; i < 100; i++) {
		void *ptr1 = malloc(50);
		void *ptr2 = malloc(500);
		void *ptr3 = malloc(5000);
		
		if (!ptr1 || !ptr2 || !ptr3) {
			data->success = 0;
			return NULL;
		}
		
		free(ptr1);
		ptr2 = realloc(ptr2, 1000);
		free(ptr2);
		free(ptr3);
	}
	
	data->success = 1;
	return NULL;
}

int main()
{
	printf("\n=== TEST 5: THREAD SAFETY (BONUS) ===\n\n");

	ft_putstr_fd("--- Test 5.1: Concurrent allocations ---\n", 1);
	pthread_t threads[N_THREADS];
	t_thread_data thread_data[N_THREADS];
	
	printf("Creating %d threads, each doing %d allocations...\n", N_THREADS, N_ALLOCS_PER_THREAD);
	
	for (int i = 0; i < N_THREADS; i++) {
		thread_data[i].thread_id = i;
		thread_data[i].n_allocs = N_ALLOCS_PER_THREAD;
		thread_data[i].success = 0;
		
		if (pthread_create(&threads[i], NULL, thread_allocate_free, &thread_data[i]) != 0) {
			ft_putstr_fd("ERROR: Failed to create thread\n", 2);
			return 1;
		}
	}
	
	int all_success = 1;
	for (int i = 0; i < N_THREADS; i++) {
		pthread_join(threads[i], NULL);
		if (!thread_data[i].success) {
			printf("Thread %d failed\n", i);
			all_success = 0;
		}
	}
	
	if (all_success) {
		ft_putstr_fd("✓ All threads completed successfully\n", 1);
	} else {
		ft_putstr_fd("✗ Some threads failed\n", 2);
	}
	
	ft_putstr_fd("\nMemory state after concurrent operations:\n", 1);
	show_alloc_mem();
	ft_putstr_fd("\n", 1);

	ft_putstr_fd("--- Test 5.2: Stress test ---\n", 1);
	printf("Creating %d threads for stress testing...\n", N_THREADS * 2);
	
	pthread_t stress_threads[N_THREADS * 2];
	t_thread_data stress_data[N_THREADS * 2];
	
	for (int i = 0; i < N_THREADS * 2; i++) {
		stress_data[i].thread_id = i;
		stress_data[i].success = 0;
		
		if (pthread_create(&stress_threads[i], NULL, thread_stress_test, &stress_data[i]) != 0) {
			ft_putstr_fd("ERROR: Failed to create thread\n", 2);
			return 1;
		}
	}
	
	all_success = 1;
	for (int i = 0; i < N_THREADS * 2; i++) {
		pthread_join(stress_threads[i], NULL);
		if (!stress_data[i].success) {
			printf("Stress thread %d failed\n", i);
			all_success = 0;
		}
	}
	
	if (all_success) {
		ft_putstr_fd("✓ All stress test threads completed successfully\n", 1);
	} else {
		ft_putstr_fd("✗ Some stress test threads failed\n", 2);
	}
	
	ft_putstr_fd("\nMemory state after stress test:\n", 1);
	show_alloc_mem();

	printf("\n=== TEST 5: PASSED ===\n\n");
	return 0;
}
