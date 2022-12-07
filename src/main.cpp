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
#include "game_log.h"
#include "robot_ai_system.h"
#include "plate_interaction_system.h"
#include "spike_death_system.h"

// Make the Map global
Map level;
GameLog gamelog;
const int MAX_RENDER_ORDER = 2;

void clear_entities(Entity entity, World& ecs) {
    auto positions = ecs.get_component_map<Position>()->component_map;
    if (!positions.empty()) {
        for (auto position : positions) {
            if (entity != position.first) {
                ecs.destroy_entity(position.first);
            }
        }
        //ecs.maintain();
    }
    auto renderables = ecs.get_component_map<Renderable>()->component_map;
    if (!renderables.empty()) {
        for (auto renderable : renderables) {
            if (entity != renderable.first){
                ecs.destroy_entity(renderable.first);
            }
        }
    }
    auto doors = ecs.get_component_map<Door>()->component_map;
    if (!renderables.empty()) {
        for (auto door : doors) {
            ecs.destroy_entity(door.first);
        }
    }
    auto connections = ecs.get_component_map<Connection>()->component_map;
    if (!connections.empty()) {
        for (auto connection : connections) {
            ecs.destroy_entity(connection.first);
        }
    }
    auto levers = ecs.get_component_map<Lever>()->component_map;
    if (!levers.empty()) {
        for (auto lever : levers) {
            ecs.destroy_entity(lever.first);
        }
    }
    auto interactables = ecs.get_component_map<Interactable>()->component_map;
    if (!interactables.empty()) {
        for (auto interactable : interactables) {
            ecs.destroy_entity(interactable.first);
        }
    }
    auto wants_interacts = ecs.get_component_map<WantsToInteract>()->component_map;
    if (!wants_interacts.empty()) {
        for (auto wants_interact : wants_interacts) {
            ecs.destroy_entity(wants_interact.first);
        }
    }
    auto stairs = ecs.get_component_map<Stairs>()->component_map;
    if (!stairs.empty()) {
        for (auto stair : stairs) {
            ecs.destroy_entity(stair.first);
        }
    }
    auto chests = ecs.get_component_map<Chest>()->component_map;
    if (!chests.empty()) {
        for (auto chest : chests) {
            ecs.destroy_entity(chest.first);
        }
    }
}

// -------------------------------------------------------------------
// Main Program

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
    init_pair(FREDBBLACK, COLOR_RED, COLOR_BLACK);
    init_pair(FGREENBBLACK, COLOR_GREEN, COLOR_BLACK);
    init_pair(FYELLOWBBLACK, COLOR_YELLOW, COLOR_BLACK);
    init_pair(FBLUEBBLACK, COLOR_BLUE, COLOR_BLACK);
    init_pair(FMAGENTABBLACK, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(FCYANBBLACK, COLOR_CYAN, COLOR_BLACK);
    init_pair(FWHITEBBLACK, COLOR_WHITE, COLOR_BLACK);

    // ---------------------------------------------------------------

    // Define levels
	
	const int A = 0;
	const int B = 1;
	const int C = 2;
	const int D = 3;
	const int E = 4;
	const int F = 5;
	const int G = 6;
	const int H = 7;
	const int I = 8;
	const int J = 9;
	const int K = 10;
	const int L = 11;
	const int M = 12;
	const int N = 13;
	const int O = 14;
	const int P = 15;
	const int Q = 16;
	const int R = 17;
	const int S = 18;
	const int T = 19;
	
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

    std::unordered_map<int, std::vector<int>> connections_baseline;

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
    connections_level_1[level.position_to_index(H, 2)] = std::vector<int>({
            level.position_to_index(E, 2),
            level.position_to_index(R, 4)});
    connections_level_1[level.position_to_index(H, 6)] = std::vector<int>({
            level.position_to_index(E, 6),
            level.position_to_index(K, 6)});
    connections_level_1[level.position_to_index(S, 7)] = std::vector<int>({
            level.position_to_index(H, 11)});

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
	connections_level_2[level.position_to_index(S, 13)] = std::vector<int>({
            level.position_to_index(E, 3)});
			
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
	connections_level_3[level.position_to_index(C, 5)] = std::vector<int>({
            level.position_to_index(G, 4),
			level.position_to_index(G, 6),
			level.position_to_index(F, 5),
			level.position_to_index(H, 5)});
	connections_level_3[level.position_to_index(G, 12)] = std::vector<int>({
            level.position_to_index(K, 4),
			level.position_to_index(K, 6),
			level.position_to_index(J, 5),
			level.position_to_index(L, 5)});
	connections_level_3[level.position_to_index(G, 5)] = std::vector<int>({
            level.position_to_index(E, 12)});
	connections_level_3[level.position_to_index(K, 5)] = std::vector<int>({
            level.position_to_index(M, 12)});		
	connections_level_3[level.position_to_index(O, 5)] = std::vector<int>({
			level.position_to_index(I, 12),
            level.position_to_index(O, 7)});	


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
	connections_level_4[level.position_to_index(C, 4)] = std::vector<int>({
            level.position_to_index(C, 5)});
	connections_level_4[level.position_to_index(G, 1)] = std::vector<int>({
            level.position_to_index(L, 4)});
	connections_level_4[level.position_to_index(R, 1)] = std::vector<int>({
            level.position_to_index(S, 7)});
	connections_level_4[level.position_to_index(N, 12)] = std::vector<int>({
            level.position_to_index(N, 9)});
	connections_level_4[level.position_to_index(P, 12)] = std::vector<int>({
            level.position_to_index(P, 9)});
	connections_level_4[level.position_to_index(R, 12)] = std::vector<int>({
            level.position_to_index(L, 1)});	

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
    level_5 += "#..!!!!.!##..!..!..#"; // 13
    level_5 += "#l.......dD......Sp#"; // 14
    level_5 += "####################"; // 15

    std::unordered_map<int, std::vector<int>> connections_level_5;
	connections_level_5[level.position_to_index(B, 13)] = std::vector<int>({
            level.position_to_index(K, 13)});
	connections_level_5[level.position_to_index(S, 13)] = std::vector<int>({
            level.position_to_index(J, 13)});

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
    ecs.register_component<Stairs>();
    ecs.register_component<Chest>();
    ecs.register_component<PressurePlate>();
    ecs.register_component<Robot>();
    ecs.register_component<Ambulates>();
    ecs.register_component<AttemptedMove>();
    ecs.register_component<Spike>();
    ecs.register_component<Dead>();

    // Register Systems
    auto interaction = ecs.register_system<Interaction>();
    interaction->components.insert(ecs.get_component_type<Position>());
    interaction->components.insert(ecs.get_component_type<WantsToInteract>());
    ecs.set_system_signature<Interaction>();

    auto robot_ai = ecs.register_system<RobotAiSystem>();
    robot_ai->components.insert(ecs.get_component_type<Robot>());
    ecs.set_system_signature<RobotAiSystem>();

    auto plate_system = ecs.register_system<PlateInteractionSystem>();
    plate_system->components.insert(ecs.get_component_type<PressurePlate>());
    ecs.set_system_signature<PlateInteractionSystem>();

    auto spike_system = ecs.register_system<SpikeDeathSystem>();
    spike_system->components.insert(ecs.get_component_type<Spike>());
    ecs.set_system_signature<SpikeDeathSystem>();

    // ---------------------------------------------------------------

    WINDOW* room = newwin(level.m_height, level.m_width, 0, 30);
    gamelog.init();

    bool quit = false;
    level.m_current_level = 5;

    RunState runstate = RunState::PreRun;

    // Create Player entity
    Entity player = ecs.create_entity();
    ecs.add_component(player, Renderable { "@", FGREENBBLACK, 10});
    ecs.add_component(player, CPlayer {});
    ecs.add_component(player, Ambulates {});

    level.create_preset_level(baseline_level, connections_baseline, player, ecs);
    ecs.add_component(player, level.index_to_position(level.m_player_start));

    while (!quit) {
        level.draw_level(room, ecs);
        std::string player_glyph = ecs.get_component<Renderable>(player).glyph;
        int player_color = ecs.get_component<Renderable>(player).symbol_color;
        int player_emphasis = A_BOLD;
        int player_x = ecs.get_component<Position>(player).x;
        int player_y = ecs.get_component<Position>(player).y;
        level.m_tile_contents[level.position_to_index(player_x, player_y)].insert(player);

        for (int render_order = 0; render_order <= MAX_RENDER_ORDER; render_order++) {
            for (auto& renderable : ecs.get_component_map<Renderable>()->component_map) {
                if (renderable.second.render_order == render_order) {
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
            }
        }

        wmove(room, player_y, player_x);
        wattron(room, COLOR_PAIR(player_color) | player_emphasis);
        wprintw(room, "%s", player_glyph.c_str());
        wattroff(room, COLOR_PAIR(player_color) | player_emphasis);

        refresh();
        wrefresh(room);
        wrefresh(gamelog.gamelog);

        // Check if something died.
        auto deaths = ecs.get_component_map<Dead>()->component_map;
        if (!deaths.empty()) {
            for (auto death : deaths) {
                if (player == death.first) {
                    ecs.remove_component<Dead>(player);
                    runstate = Player::kill_player();
                }
            }
        }

        switch(runstate) {
            // A new level must be created.
            case RunState::PreRun:
            {
                level.m_tiles.clear();
                level.m_blocked_tiles.clear();
                level.m_doors.clear();
                for (auto tile_content : level.m_tile_contents) {
                    tile_content.clear();
                }
                level.m_tile_contents.clear();
                clear_entities(player, ecs);

                // Determine which level it is.
                switch (level.m_current_level) {
                    case 1:
                    {
                        level.create_preset_level(level_1, connections_level_1, player, ecs);
                        Position& player_pos = ecs.get_component<Position>(player);
                        Position player_start = level.index_to_position(level.m_player_start);
                        player_pos.x = player_start.x;
                        player_pos.y = player_start.y;
                        gamelog.printlog(std::string("You enter level " + std::to_string(level.m_current_level) + ".").c_str());
                        break;
                    }
                    case 2:
                    {
                        level.create_preset_level(level_2, connections_level_2, player, ecs);
                        Position& player_pos = ecs.get_component<Position>(player);
                        Position player_start = level.index_to_position(level.m_player_start);
                        player_pos.x = player_start.x;
                        player_pos.y = player_start.y;
                        gamelog.printlog(std::string("You enter level " + std::to_string(level.m_current_level) + ".").c_str());
                        break;
                    }
                    case 3:
                    {
                        level.create_preset_level(level_3, connections_level_3, player, ecs);
                        Position& player_pos = ecs.get_component<Position>(player);
                        Position player_start = level.index_to_position(level.m_player_start);
                        player_pos.x = player_start.x;
                        player_pos.y = player_start.y;
                        gamelog.printlog(std::string("You enter level " + std::to_string(level.m_current_level) + ".").c_str());
                        gamelog.printlog("You feel a mystical link to your very soul.");
                        break;
                    }
                    case 4:
                    {
                        level.create_preset_level(level_4, connections_level_4, player, ecs);
                        Position& player_pos = ecs.get_component<Position>(player);
                        Position player_start = level.index_to_position(level.m_player_start);
                        player_pos.x = player_start.x;
                        player_pos.y = player_start.y;
                        gamelog.printlog(std::string("You enter level " + std::to_string(level.m_current_level) + ".").c_str());
                        break;
                    }
                    case 5:
                    {
                        level.create_preset_level(level_5, connections_level_5, player, ecs);
                        Position& player_pos = ecs.get_component<Position>(player);
                        Position player_start = level.index_to_position(level.m_player_start);
                        player_pos.x = player_start.x;
                        player_pos.y = player_start.y;
                        gamelog.printlog(std::string("You enter level " + std::to_string(level.m_current_level) + ".").c_str());
                        gamelog.printlog("You feel a mystical link to your very soul.");
                        break;
                    }
                }
                ecs.run_systems(ecs);
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

