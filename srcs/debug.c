/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jikaewsi <strixz.self@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 01:03:22 by jikaewsi          #+#    #+#             */
/*   Updated: 2025/11/17 01:30:02 by jikaewsi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_malloc.h"

t_malloc_config g_config = {
    .is_initialized = false,
    .is_debug = false,
    .is_check = false,
    .is_scribble = false
};

/**
 * @brief Helper to check if environment variable is set and not "0"
 */
static bool is_env_enabled(const char *name) {

    char *value = getenv(name);

    if (value == NULL)
        return false;
    
    if (value[0] == '0' && value[1] == '\0')
        return false;
    
    return 1;

}

/**
 * @brief Initialize malloc configuration from environment variables
 * 
 * Supported variables:
 * - MALLOC_DEBUG: Enable verbose logging
 * - MALLOC_CHECK: Enable pointer validation
 * - MALLOC_SCRIBBLE: Fill freed memory with 0x55 pattern
 */
void init_malloc_config(void) {

    if (g_config.is_initialized)
        return;
    
    g_config.is_debug = is_env_enabled("MALLOC_DEBUG");
    g_config.is_check = is_env_enabled("MALLOC_CHECK");
    g_config.is_scribble = is_env_enabled("MALLOC_SCRIBBLE");
    
    g_config.is_initialized = true;
    
    // Print configuration if debug is enabled
    if (g_config.is_debug) {
        ft_putstr_fd("\n[MALLOC_CONFIG] Initialized with:\n", 2);
        ft_putstr_fd("  MALLOC_DEBUG: ", 2);
        ft_putstr_fd(g_config.is_debug ? "ON\n" : "OFF\n", 2);
        ft_putstr_fd("  MALLOC_CHECK: ", 2);
        ft_putstr_fd(g_config.is_check ? "ON\n" : "OFF\n", 2);
        ft_putstr_fd("  MALLOC_SCRIBBLE: ", 2);
        ft_putstr_fd(g_config.is_scribble ? "ON\n" : "OFF\n", 2);
        ft_putstr_fd("\n", 2);
    }

}

/**
 * @brief Validates that a pointer was allocated by our malloc
 * @param ptr Pointer to validate
 * @return true if valid, false if invalid
 */
bool is_valid_pointer(void *ptr) {

    if (ptr == NULL)
        return false;
    
    t_block_metadata *metadata = (t_block_metadata *)((char *)ptr - aligned_header_size());

    t_block_metadata *large_block = g_tracker.used_large_chunk;
    
    while (large_block) {

        if (large_block == metadata)
            return true;

        large_block = large_block->next;

    }
    
    t_zone_metadata *zone = g_tracker.tiny_chunk;

    while (zone) {

        t_block_metadata *block = zone->used_blocks;
        
        while (block) {
        
            if (block == metadata)
                return true;
        
            block = block->next;
        
        }
        
        zone = zone->next;
    
    }
    
    zone = g_tracker.small_chunk;

    while (zone) {
    
        t_block_metadata *block = zone->used_blocks;
    
        while (block) {
    
            if (block == metadata)
                return true;
    
            block = block->next;
    
        }
    
        zone = zone->next;
    
    }
    
    return false;

}
