#ifndef DEFINES_H_INCLUDED
#define DEFINES_H_INCLUDED


#include <string>
#include <vector>



/**
    ...OFFSET : address on which we have to add the game's base address and get the address where the value is located directly
    ...POINTER_OFFSET : address on which we have to add the game's base address and get the address where another address lies
    ...OFFSETS : offsets with which a baseAddress + POINTER_OFFSET address has to be dereferenced
**/
/** Window Name**/
#define GAME_NAME L"Mount&Blade Warband"


/** Server Graph File Name to read from**/
#define SERVER_GRAPH_URL L"servergraph"
//#define SERVER_GRAPH_HTTP_APPEND "/ow.php?event=8"


/** Time in ms to wait between clicks  (=menu traversation) **/
#define CLICK_WAIT_TIME 1000

/** travel direction **/
#define TRAVEL_DIR_NOOP -1
#define TRAVEL_DIR_REJOIN -2
#define TRAVEL_DIR_NORTH 0
#define TRAVEL_DIR_EAST 1
#define TRAVEL_DIR_SOUTH 2
#define TRAVEL_DIR_WEST 3

/** File Parser **/
#define FILE_MAX_CHARS 65535
#define FILE_NUM_COLUMNS 9
#define FILE_COLUMN_TO_NORTH_INDEX 2
#define FILE_COLUMN_TO_EAST_INDEX 3
#define FILE_COLUMN_TO_SOUTH_INDEX 4
#define FILE_COLUMN_TO_WEST_INDEX 5
#define FILE_COLUMN_MAP_NAME_INDEX 0
#define FILE_COLUMN_IP_INDEX 6
#define FILE_COLUMN_PORT_INDEX 7
//base adress (on my machine, is not referenced at all in this proj): 4194304
//s0 10302824
//s1 addr_offset: 10302968
//s2 addr_offset: 10303112
//s3 10303256
//s4 10303400

// string reg offsets
#define STRING_REG_0_ADDR_OFFSET 10302824
#define STRING_REG_1_ADDR_OFFSET 10302968
#define STRING_REG_2_ADDR_OFFSET 10303112
#define STRING_REG_3_ADDR_OFFSET 10303256
#define STRING_REG_4_ADDR_OFFSET 10303400
#define STRING_REG_20_ADDR_OFFSET 10305704

//reg offsets
#define REG_0_ADDR_OFFSET 10293592
#define REG_1_ADDR_OFFSET 10293600
#define REG_2_ADDR_OFFSET 10293608
#define REG_3_ADDR_OFFSET 10293616

/** travel request params DEPRECATED**/
#define TRAVEL_REQUEST_NORTH "will travel to the North"
#define TRAVEL_REQUEST_WEST "will travel to the West"
#define TRAVEL_REQUEST_SOUTH "will travel to the South"
#define TRAVEL_REQUEST_EAST "will travel to the East"
//new travel request
#define TRAVEL_REQUEST_MESSAGE "will travel to the"
//
#define TRAVEL_REQUEST_ADDR_OFFSET 10303112
//deprecated #define TRAVEL_REQUEST_STRING_LENGTH 24
#define TRAVEL_REQUEST_STRING_LENGTH 18

/** character screen event **/
#define CHAR_SCREEN_REACHED_EVENT_MESSAGE "character menu reached"
#define CHAR_SCREEN_REACHED_EVENT_ADDR_OFFSET 10303256
#define CHAR_SCREEN_REACHED_EVENT_STRING_LENGTH 22

/** current map name **/
#define MAP_NAME_ADDR_OFFSET 10303400
#define MAP_NAME_LENGTH_CONVENTION 17


/** joined server recently event **/
#define SERVER_JOINED_EVENT_MESSAGE "joined server"
#define SERVER_JOINED_EVENT_ADDR_OFFSET 10302968
#define SERVER_JOINED_EVENT_STRING_LENGTH 13

/** params for the ip address of joined/current selected server **/
#define SERVER_INFO_IP_POINTER_OFFSET 10328896
#define SERVER_INFO_IP_OFFSETS {176,200}
#define SERVER_INFO_IP_LENGTH_POINTER_OFFSET 10328896
#define SERVER_INFO_IP_LENGTH_OFFSETS {176,196}

/** server list entry: port **/
#define SERVER_INFO_PORT_POINTER_OFFSET 10328896
#define SERVER_INFO_PORT_OFFSETS {516}


/**  navigating inside the server list **/
#define SERVER_LIST_INFO_CUR_SEL_INDEX_POINTER_OFFSET 48670912
#define SERVER_LIST_INFO_CUR_SEL_INDEX_OFFSETS {688}
#define SERVER_LIST_INFO_IS_IN_SERVER_LIST_OFFSET  10329560
#define SERVER_LIST_INFO_IS_IN_SERVER_LIST_TRUE_VAL 2
#define SERVER_LIST_INFO_WATCH_ENTRIES_UNTIL_SCROLLDOWN 20
#define SERVER_LIST_INFO_SCROLLDOWN_STEPS 2
#define SERVER_LIST_INFO_WAIT_TIME_UNTIL_IP_READ 200
/** Time in ms to wait for game to fill server list **/
#define SERVER_LIST_INFO_WAIT_TIME 30000

/** navigating in the filter panel inside the server list. "Base"-pointer address is the same for all entries of this panel **/
#define FILTER_PANEL_POINTER_OFFSET 10329264
#define FILTER_PANEL_ACTIVE_CHECKED_OFFSETS {220}
#define FILTER_PANEL_HAS_PLAYERS_CHECKED_OFFSETS {224}
#define FILTER_PANEL_IS_VERSION_COMPATIBLE_CHECKED_OFFSETS {248}
#define FILTER_PANEL_IS_PASSWORD_FREE_CHECKED_OFFSETS {232}
#define FILTER_PANEL_MATCH_MODE_INDEX_OFFSETS {244}
#define FILTER_PANEL_PING_LIMIT_INDEX_OFFSETS {240}



/** window where game content is rendered **/
#define WINDOW_EFFECTIVE_SIZE_Y_OFFSET 4637504
#define WINDOW_EFFECTIVE_SIZE_X_OFFSET 4637500

/**/
#define GAME_IS_FULLSCREEN_ADDR_OFFSET 1786348


//x, y in percent of window pixel length

//ASSUMING FILTER PANEL IS OPENED!!!
#define SERVER_LIST_FIRST_ENTRY_X 40
#define SERVER_LIST_FIRST_ENTRY_Y 32
#define SERVER_LIST_LAST_ENTRY_X 40
#define SERVER_LIST_LAST_ENTRY_Y 76

#define SERVER_LIST_NEXT_ENTRY_Y 2

#define BUTTON_JOIN_SERVER_X 83
#define BUTTON_JOIN_SERVER_Y 91

#define BUTTON_REFRESH_SERVER_LIST_X 46
#define BUTTON_REFRESH_SERVER_LIST_Y 4


#define BUTTON_JOIN_SERVER_LIST_X 75
#define BUTTON_JOIN_SERVER_LIST_Y 50


#define BUTTON_DROP_DOWN_NETWORK_X 26
#define BUTTON_DROP_DOWN_NETWORK_Y 4

#define BUTTON_KICKED_OK_X 48
#define BUTTON_KICKED_OK_Y 63


#define BUTTON_DROP_DOWN_NETWORK_INTERNET_X 27
#define BUTTON_DROP_DOWN_NETWORK_INTERNET_Y 17

//for debug use only: LAN Mode
//#define BUTTON_DROP_DOWN_NETWORK_INTERNET_X 27
//#define BUTTON_DROP_DOWN_NETWORK_INTERNET_Y 14
//-----------------



#define BUTTON_FILTER_PANEL_X 78
#define BUTTON_FILTER_PANEL_Y 5

#define BUTTON_FILTER_HAS_PLAYERS_X 9
#define BUTTON_FILTER_HAS_PLAYERS_Y 12

#define BUTTON_FILTER_IS_VERSION_COMPATIBLE_X 9
#define BUTTON_FILTER_IS_VERSION_COMPATIBLE_Y 16

#define BUTTON_FILTER_IS_PASSWORD_FREE_X 9
#define BUTTON_FILTER_IS_PASSWORD_FREE_Y 19

#define BUTTON_FILTER_MATCH_MODE_PREV_X 62
#define BUTTON_FILTER_MATCH_MODE_PREV_Y 13
#define BUTTON_FILTER_PING_LIMIT_PREV_X 62
#define BUTTON_FILTER_PING_LIMIT_PREV_Y 18





#define MOUSE_LEFT_CLICK 0
#define MOUSE_RIGHT_CLICK 1
#define MOUSE_SCROLL_DOWN 2



#endif // DEFINES_H_INCLUDED
