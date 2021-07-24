#include <stdlib.h>
#include <stdio.h>
#include "../types/map.h"

void update_graph(Map_t *map) {
    // Preprocess - clean segments
    for (int k = 0; k < map->segment_count; k++) {
        Segment_t *segment = map->segments[k];
        segment->gs_distance_to_initial = -1;
        segment->gs_distance_to_target = -1;
        segment->gs_factor = 0;
        segment->gs_visited = 0;
    }
    
    // Set the initial segment properties
    map->initial_segment->gs_distance_to_initial = 0;
    map->initial_segment->gs_visited = 1;

    // Breadth search assigning distance and factor
    Segment_t **queue_segments = malloc(sizeof(Segment_t *) * map->segment_count);
    int current_segment_place = 0;
    int current_segment_iteration = 0;

    queue_segments[current_segment_place] = map->initial_segment;
    current_segment_place += 1;

    while (current_segment_iteration < current_segment_place) {
        Segment_t *current_segment = queue_segments[current_segment_iteration];
        current_segment->gs_factor += current_segment->frontiers_count;

        // For each segment I'm touching
        int frontier_segments_count;
        Segment_t **frontier_segments = get_all_frontier_segments(current_segment, &frontier_segments_count);

        for (int k = 0; k < frontier_segments_count; k++) {
            Segment_t *frontier_segment = frontier_segments[k];

            // If not visited, assign distance and set visited
            if (!frontier_segment->gs_visited) {
                frontier_segment->gs_visited = 1;
                frontier_segment->gs_distance_to_initial = current_segment->gs_distance_to_initial + 1;

                // Add to the queue
                queue_segments[current_segment_place] = frontier_segment;
                current_segment_place += 1;
            }

            if (current_segment->gs_distance_to_initial < frontier_segment->gs_distance_to_initial) {
                // Increase the frontier segment gs_factor by my factor
                frontier_segment->gs_factor += current_segment->frontiers_count;
            }
        }

        current_segment_iteration += 1;
    }

    // By now, we have the furthest segments
    // blz, fechou o de geral. agora tem q escolher qual que vai pegar. isso pode ser feito no while de cima inclusive
    // - pega o segmento mais distante e com maior interconectedness. em caso de empate, pega o ultimo memo e foda-se

    // beleza, agora 

    // passa zerando o visitado

    // f -> fila de segmentos
    // empilha segmento escolhido
    // enquanto fila nao vazia
    //     s -> topo da fila
    //     para cada segmento vizinho de s atual
    //         se segmento nao visitado
    //             empilha segmento
    //         se distancia == -1 ou distancia > minha distancia
    //             distance_target = s.distance_target +1

    // beleza, agora repte x vezes: 
    //     olha pros segmento vizinho, pega só os que tem a menor distancia do mais longe
    //     agrega as cor e soma os interconectedness
    //     pega a cor que tiver a maior soma
    //     pinta o mapa
}

void solve_most_distant_segment(Map_t *map, int moves_before_recalculating) {
    while (map->segment_count > 1) {
        update_graph(map);
        print_full_map(map);
        break;
    }
}