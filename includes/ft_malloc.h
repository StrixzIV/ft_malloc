/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jikaewsi <strixz.self@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 03:18:25 by jikaewsi          #+#    #+#             */
/*   Updated: 2025/11/17 01:34:32 by jikaewsi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MALLOC_H
# define FT_MALLOC_H

# include <assert.h>
# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include <sys/mman.h>

# include "../libft/libft.h"

# define HEXDUMP_SIZE 128

# define MIN_ALIGNMENT 16
# define MIN_FRAGMENTATION_SIZE 64

# define TINY_BLOCK_SIZE 256
# define SMALL_BLOCK_SIZE 2048
# define MIN_BLOCK_COUNT_IN_ZONE 128
# define TINY_ALLOC_SIZE (TINY_BLOCK_SIZE - aligned_header_size())
# define SMALL_ALLOC_SIZE (SMALL_BLOCK_SIZE - aligned_header_size())

# ifdef __APPLE__
#  define PAGE_SIZE ((size_t) getpagesize())
# elif defined(__linux__)
#  define PAGE_SIZE ((size_t) sysconf(_SC_PAGESIZE))
# else
#  error "Unsupported operating system"
# endif

typedef struct s_malloc_config {
    bool is_initialized;
    bool is_debug;
    bool is_check;
    bool is_scribble;
}   t_malloc_config;

typedef struct s_block_metadata {
    struct s_block_metadata     *prev;
    struct s_block_metadata     *next;
    struct s_zone_metadata      *zone;
    size_t                      block_size;
}   t_block_metadata;

typedef struct s_zone_metadata {
    struct s_zone_metadata  *prev;
    struct s_zone_metadata  *next;
    t_block_metadata        *used_blocks;
    t_block_metadata        *freed_blocks;
    size_t                  allocated_size;
}   t_zone_metadata;

typedef struct s_malloc_tracker {
    pthread_mutex_t     alloc_lock;
    t_zone_metadata     *tiny_chunk;
    t_zone_metadata     *small_chunk;
    t_block_metadata    *free_large_chunk;
    t_block_metadata    *used_large_chunk;
}   t_malloc_tracker;

extern t_malloc_config  g_config;
extern t_malloc_tracker g_tracker;

// Helpers

void            add_block(t_block_metadata **lst_head, t_block_metadata *header);
void            add_zone(t_zone_metadata **lst_head, t_zone_metadata *header);
void            remove_block(t_block_metadata **lst_head, t_block_metadata *header);
void            remove_zone(t_zone_metadata **lst_head, t_zone_metadata *header);

void            sort(void **head, size_t count);
void            put_unbr_fd(size_t nb, int fd);
void            put_hex_fd(size_t nb, int fd);
void            put_hex_byte(unsigned char byte, int fd);
void            print_hex_dump(void *addr, size_t size);

void            init_malloc_config(void);
bool            is_valid_pointer(void *ptr);

__uint64_t      align_value(size_t value, size_t alignment);
size_t          aligned_header_size(void);
size_t          get_aligned_large_block_size(size_t size);
size_t          get_zone_headers_mem_usage(size_t block_size);

void            *allocate(void *address, size_t size);
void            *create_alloc_zone(t_zone_metadata **lst_head, size_t block_size);
void            *allocate_block(t_zone_metadata *zone, size_t size);
void            free_block(t_block_metadata *block);

void            *intern_malloc(size_t size);
void            intern_free(void *ptr);

// Mandatory functions

void	        free(void *ptr);
void	        *malloc(size_t size);
void	        *realloc(void *ptr, size_t size);

void	        show_alloc_mem();
void            show_alloc_mem_ex();

#endif
