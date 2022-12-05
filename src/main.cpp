#include <ncurses.h>
#include <locale>
#include <string>
#include <unordered_map>

#include "components.h"
#include "map.h"
#include "world.h"
#include "player.h"
#include "run_state.h"
#include "interaction_system.h"
#include "toggle_connections_system.h"

// Make the Map global
Map level;

int main() {
    // ---------------------------------------------------------------
    // preliminary set up for ncurses to use support all characters
    // and start colors.
    setlocale(LC_ALL, "");
    initscr();

    if (!has_colors()) {
        printw("This terminal does not support color.");
        mvprintw(1, 0, "Please use a terminal that does support color.");
        getch();
        return -1;
    }
    
    //noecho();
    curs_set(0); // hide the cursor
    keypad(stdscr, true);
    start_color();
    // ---------------------------------------------------------------

    // ---------------------------------------------------------------
    // Initialize colors.
    init_pair(FWHITEBBLACK, COLOR_WHITE, COLOR_BLACK);
    init_pair(FYELLOWBBLACK, COLOR_YELLOW, COLOR_BLACK);
    init_pair(FGREENBBLACK, COLOR_GREEN, COLOR_BLACK);

    // ---------------------------------------------------------------


    // Define levels
    std::string baseline_level;
    baseline_level += "####################";
    baseline_level += "#..................#";
    baseline_level += "#..................#";
    baseline_level += "#..................#";
    baseline_level += "#..................#";
    baseline_level += "#..................#";
    baseline_level += "#..................#";
    baseline_level += "#..................#";
    baseline_level += "#..................#";
    baseline_level += "#..................#";
    baseline_level += "#..................#";
    baseline_level += "#..................#";
    baseline_level += "#..................#";
    baseline_level += "#..................#";
    baseline_level += "####################";

    std::string level_1;
    level_1 += "####################"; // 1
    level_1 += "#...#.....#........#"; // 2
    level_1 += "#.c.D..l..#.S......#"; // 3
    level_1 += "#...#.....#........#"; // 4
    level_1 += "#####.....#######d##"; // 5
    level_1 += "#...#.....#........#"; // 6
    level_1 += "#...d..l..D........#"; // 7
    level_1 += "#...#.....#.......l#"; // 8
    level_1 += "#...#.....#!!!!!!!!#"; // 9
    level_1 += "#...#.....#........#"; // 10
    level_1 += "#...#.....#........#"; // 11
    level_1 += "#...###D###........#"; // 12
    level_1 += "#.@.#.....#........#"; // 13
    level_1 += "#...#.....#........#"; // 14
    level_1 += "####################"; // 15

    std::unordered_map<int, std::vector<int>> connections_level_1;
    connections_level_1[level.position_to_index(7, 2)] = std::vector<int>({
            level.position_to_index(4, 2),
            level.position_to_index(17, 4)});
    connections_level_1[level.position_to_index(7, 6)] = std::vector<int>({
            level.position_to_index(4, 6),
            level.position_to_index(10, 6)});
    connections_level_1[level.position_to_index(18, 7)] = std::vector<int>({
            level.position_to_index(7, 11)});

    std::string level_2;
    level_2 +=  "####################"; // 1
    level_2 +=  "#...#.#....#@..#...#"; // 2
    level_2 +=  "#.S.#.#.##.#s#.#.#.#"; // 3
    level_2 +=  "#...D.#.##.###...#.#"; // 4
    level_2 +=  "#####.#..#...#.#.#.#"; // 5
    level_2 +=  "#.....##.###.#.#.#.#"; // 6
    level_2 +=  "#.####...#...#.#...#"; // 7
    level_2 +=  "#.#....###.###.#####"; // 8
    level_2 +=  "#.#.###........#####"; // 9
    level_2 +=  "#.....#.######.....#"; // 10
    level_2 +=  "#...#.#.#...#......#"; // 11
    level_2 +=  "###.#.#.#......#####"; // 12
    level_2 +=  "#.###.#.########...#"; // 13
    level_2 +=  "#.....#..........#l#"; // 14
    level_2 +=  "####################"; // 15

    std::unordered_map<int, std::vector<int>> connections_level_2;

    std::string level_3;
    level_3 += "####################"; // 1
    level_3 += "#.s.#.R.#...#.....S#"; // 2
    level_3 += "#.@.#...#...#......#"; // 3
    level_3 += "#...#...#...#.R....#"; // 4
    level_3 += "#...#.d.#.d.#.#....#"; // 5
    level_3 += "#.l.#dpd#dpd#.p....#"; // 6
    level_3 += "#...#.d.#.d.#......#"; // 7
    level_3 += "#...#...#.R.##d#####"; // 8
    level_3 += "#...#########......#"; // 9
    level_3 += "#...#...#...#......#"; // 10
    level_3 += "#...#...#...#......#"; // 11
    level_3 += "#...#...#...#......#"; // 12
    level_3 += "#...D.l.d...D......#"; // 13
    level_3 += "#...#...#...#......#"; // 14
    level_3 += "####################"; // 15

    std::unordered_map<int, std::vector<int>> connections_level_3;

    std::string level_4;
    level_4 += "####################"; // 1
    level_4 += "#.s.#.l....D.c#..l!#"; // 2
    level_4 += "#.@.#......####...!#"; // 3
    level_4 += "#...#####..#.!!!..!#"; // 4
    level_4 += "#.p........D.!!!..!#"; // 5
    level_4 += "##d#########.!!!..!#"; // 6
    level_4 += "#...#......#.......#"; // 7
    level_4 += "#.l.##############D#"; // 8
    level_4 += "#####......D.......#"; // 9
    level_4 += "#..........##d#d#d##"; // 10
    level_4 += "#..........##.#.#.##"; // 11
    level_4 += "######..#####.!.!.##"; // 12
    level_4 += "#..........##l#l#l##"; // 13
    level_4 += "#..S.......#########"; // 14
    level_4 += "####################"; // 15

    std::unordered_map<int, std::vector<int>> connections_level_4;

    std::string level_5;
    level_5 += "####################"; // 1
    level_5 += "#s.......##!!!!!!!!#"; // 2
    level_5 += "#@.!.....##R.......#"; // 3
    level_5 += "#..!.....##!.......#"; // 4
    level_5 += "#..!!!!..##......!.#"; // 5
    level_5 += "#........##.!!.!.!.#"; // 6
    level_5 += "#......!.##....!...#"; // 7
    level_5 += "#!.!.!.!.##.!.!....#"; // 8
    level_5 += "#........##........#"; // 9
    level_5 += "#.!!!.!!.##....!!..#"; // 10
    level_5 += "#..!!..!.##....!...#"; // 11
    level_5 += "#......c.##.!!.....#"; // 12
    level_5 += "#..!!!!.!##..!..!.!#"; // 13
    level_5 += "#l.......d.......Sp#"; // 14
    level_5 += "####################"; // 15

    std::unordered_map<int, std::vector<int>> connections_level_5;

    // ---------------------------------------------------------------


    // ---------------------------------------------------------------
    // Initialize the ECS.

    World ecs;
    ecs.init();

    // Register Components
    ecs.register_component<Position>();
    ecs.register_component<Renderable>();
    ecs.register_component<CPlayer>();
    ecs.register_component<Door>();
    ecs.register_component<Connection>();
    ecs.register_component<Lever>();
    ecs.register_component<Interactable>();
    ecs.register_component<WantsToInteract>();
    ecs.register_component<WantsToToggleConnections>();

    // Register Systems
    auto interaction = ecs.register_system<Interaction>();
    interaction->components.insert(ecs.get_component_type<Position>());
    interaction->components.insert(ecs.get_component_type<WantsToInteract>());
    ecs.set_system_signature<Interaction>();

    // ---------------------------------------------------------------

    WINDOW* room = newwin(level.m_height, level.m_width, 5, 10);

    bool quit = false;
    RunState runstate = RunState::PreRun;

    level.create_preset_level(level_1, connections_level_1, ecs);
    // Create Player entity
    Entity player = ecs.create_entity();
    ecs.add_component(player, level.index_to_position(level.m_player_start));
    ecs.add_component(player, Renderable { "@", FWHITEBBLACK });

    while (!quit) {
        level.draw_level(room, ecs);
        std::string player_glyph = ecs.get_component<Renderable>(player).glyph;
        int player_color = ecs.get_component<Renderable>(player).symbol_color;
        int player_x = ecs.get_component<Position>(player).x;
        int player_y = ecs.get_component<Position>(player).y;
        level.m_tile_contents[level.position_to_index(player_x, player_y)].push_back(player);
        for (auto& renderable : ecs.get_component_map<Renderable>()->component_map) {
            Entity entity = renderable.first;
            if (entity != player) {
                std::string glyph = renderable.second.glyph;
                int color = renderable.second.symbol_color;
                auto& position = ecs.get_component<Position>(entity);

                wmove(room, position.y, position.x);
                wattron(room, COLOR_PAIR(color));
                wprintw(room, "%s", glyph.c_str());
                wattroff(room, COLOR_PAIR(color));
            }
        }

        wmove(room, player_y, player_x);
        wattron(room, COLOR_PAIR(player_color));
        wprintw(room, "%s", player_glyph.c_str());
        wattroff(room, COLOR_PAIR(player_color));

        refresh();
        wrefresh(room);

        switch(runstate) {
            case RunState::PreRun: {
                runstate = RunState::PlayerInput;
                break;
            }
            case RunState::PlayerInput:
            {
                runstate = Player::player_input(player, level, ecs);
                break;
            }
            case RunState::PlayerTurn:
            {
                ecs.run_systems(ecs);
                runstate = RunState::AiTurn;
                break;
            }

            case RunState::AiTurn:
            {
                ecs.run_systems(ecs);
                runstate = RunState::PlayerInput;
                break;
            }

            case RunState::Exit:
            {
                quit = true;
                break;
            }
            default:
            {
                ecs.run_systems(ecs);
                runstate = RunState::PlayerInput;
                break;
            }
        }

    }

    endwin();
    
    return 0;
}
