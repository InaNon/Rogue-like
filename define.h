#ifndef DEF_define
#define DEF_define

/*デバッグ用*/
static const int DEBUG_MODE_MAP = false;
static const int DEBUG_MODE_CAMERA = false;
static const bool DEBUG_F = false;
static const bool DEBUG_MINI_MAP_FULL_OPEN = true;
static const bool DEBUG_MODE_DARK = true;

/************/

//takano
static const int ZOOM = 1;
static const int EXP_MAP_X = 22;
static const int EXP_MAP_Y = 16;

static const int CHIP_X_SIZE = 32;//ina 32
static const int CHIP_Y_SIZE = 32;//ina 32

static const int EXPCHIPSIZE_X = EXP_MAP_X;
static const int EXPCHIPSIZE_Y = EXP_MAP_Y;

static const int MAP_X_MAX = 64;
static const int MAP_Y_MAX = 64;//ina 48

static const int EXPMAP_X_MAX = MAP_X_MAX + EXPCHIPSIZE_X;
static const int EXPMAP_Y_MAX = MAP_Y_MAX + EXPCHIPSIZE_Y;

static const int WINDOWSIZE_X = EXP_MAP_X * CHIP_X_SIZE;
static const int WINDOWSIZE_Y = EXP_MAP_Y * CHIP_Y_SIZE;


//ina0125
//static const int WINDOW_ZOOM = 1;

static const int ORIGIN_WINDOWSIZE_X = EXP_MAP_X * CHIP_X_SIZE;
static const int ORIGIN_WINDOWSIZE_Y = EXP_MAP_Y * CHIP_Y_SIZE;

//static const int WINDOWSIZE_X = EXP_MAP_X * CHIP_X_SIZE * WINDOW_ZOOM;
//static const int WINDOWSIZE_Y = EXP_MAP_Y * CHIP_Y_SIZE * WINDOW_ZOOM;
//static const int MINIMAP_CELL_SIZE = 2;


//static const int ZOOM = 1;

/*
static const int CHIP_X_SIZE = 32;
static const int CHIP_Y_SIZE = 32;

static const int ZOOM = 1;

static const int EXPCHIPSIZE_X = 20;
static const int EXPCHIPSIZE_Y = 16;

static const int MAP_X_MAX = 64;
static const int MAP_Y_MAX = 48;

static const int EXPMAP_X_MAX = MAP_X_MAX + EXPCHIPSIZE_X;
static const int EXPMAP_Y_MAX = MAP_Y_MAX + EXPCHIPSIZE_Y;

static const int WINDOWSIZE_X = EXPCHIPSIZE_X * CHIP_X_SIZE;
static const int WINDOWSIZE_Y = EXPCHIPSIZE_Y * CHIP_Y_SIZE;
*/

static const int MIN_ROOM_SIZE = 3;
static const int MIN_SECTION_SIZE = MIN_ROOM_SIZE + 4;

static const int MINIMAP_CELL_SIZE = 2;

/*いな*/
static const int UNIT_MAX = 256;

static const int MESSAGE_MAX = 64;
static const int MAX_TEXT_LENGTH = 64;

static const int MARGIN = 10;
static const int CHAR_SIZE = 16;
static const int MAX_CONTENT_NUM = 128;
static const int LIST_BOX_MAX = 64;

static const int OLD_MAX = 16;

static const int ITEM_DATA_MAX = 256;
static const int UNIT_DATA_MAX = 256;
static const int SOUND_DATA_MAX = 256;


static const int ITEM_MAX = 128;

static const int COUNT_MARGIN = 8;

static const int ITEM_STOCK_MAX = 128;
static const int NO_ITEM_STOCK_NUM = -1;

static const int ADD_ATK = 2;
static const int ADD_MAX_HP = 4;
static const int ADD_DEF = 2;
static const int ADD_SPEAD = 2;
static const int ADD_LUK = 1;

static const int COMMAND_MAX = 32;

static const int ALL_IMAGE_CHIP_X = 10;
static const int ALL_IMAGE_CHIP_Y = 2;
static const int IMAGE_CHIP_SIZE_X = 24;
static const int IMAGE_CHIP_SIZE_Y = 24;




enum BELONG {
	PLAYER,
	SHOP,
};

enum ITEM_KIND {
	STATUS_ITEM,
	EQUIP_ITEM,
};

enum EQUIPMENT_KIND {
	SWORD,
	SHIELD,
	RING,
};



enum SHAVE_F {
	SHAVE_FALSE,
	SHAVE_SLANT_TRUE,
	SHAVE_ALL_TRUE,
};

enum DUNGEON_MAKE_MODE {
	DEPTH_FIRST_RAND,
	DEPTH_FIRST_LARGER,
	WIDTH_FIRST,
	DEPTH_FIRST_DEVIDE_LARGER,
	EVEN_DEVIDE,
};

enum MINIMAP {
	MINIMAP_FLOOR,
	MINIMAP_STEP,
	MINIMAP_PLAYER,
	MINIMAP_ENEMY,
	MINIMAP_ITEM,
	MINIMAP_NUM,
};

enum BOXNUM {
	MENU,
	ITEM,
	EQUIP,
	STATUS,
	FOOT,
	SAVE,
	USE_ITEM,
	PUT_ON,
	PUT_OFF,
	EXPLAIN,
	NOBOX = 63,
};


enum CELLTYPE {
	NONE_CELLTYPE,
	ROOM_FLOOR,
	ROAD_FLOOR,
	BOX_WALL,
	SLANT_WALL,
	ROOM_STEP,
	ROAD_STEP,
	TRAP_FLOOR,
	SHOP_FLOOR,
	CELLTYPE_NUM
};

enum AUTO_CELL_TYPE {
	UP_LEFT_CELL,
	UP_CELL,
	UP_RIGHT_CELL,
	LEFT_CELL,
	CENTER_CELL,
	RIGHT_CELL,
	DOWN_LEFT_CELL,
	DOWN_CELL,
	DOWN_RIGHT_CELL,
	UP_LEFT_EMPTY_CELL,
	UP_RIGHT_EMPTY_CELL,

	DOWN_LEFT_EMPTY_CELL = 12,
	DOWN_RIGHT_EMPTY_CELL,

	AUTO_CELL_TYPE_NUM = 15
};

/*
enum DIRECTION {
	NONE_DIRECTION, DIR_LEFT, DIR_UP, DIR_RIGHT, DIR_DOWN
};
*/


enum COMMAND {
	UP = 1,
	UP_RIGHT,
	RIGHT,
	DOWN_RIGHT,
	DOWN,
	DOWN_LEFT,
	LEFT,
	UP_LEFT,
	STOP,
	ATTACK,
	NOTHING = 100
};

enum DIRECTION {
	NONE_DIRECTION,
	DIR_UP,
	DIR_UP_RIGHT,
	DIR_RIGHT,
	DIR_DOWN_RIGHT,
	DIR_DOWN,
	DIR_DOWN_LEFT,
	DIR_LEFT,
	DIR_UP_LEFT,
};

enum DUNGEON_KIND {
	FOREST,
	CAVE,
	LAVA,
	LAKE,
	REMAINS
};

enum EPIDEMICITY {
	GROWTH,
	PEAK,
	DECAY
};

#endif