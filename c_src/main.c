#include "gc.h"
#include <assert.h>
#include <stdio.h>

// lua

#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"

// list

#include "fifolist.h"

//
#define CommonHeader int type

typedef struct CMoonCom_Load {

	CommonHeader;
	const char* filename;

} CMoonCom_Load;

typedef struct CMoonCom_Eval {

	CommonHeader;

	const char* express;

} CMoonCom_Eval;

typedef struct CMoonCom_Call {

} CMoonCom_Call;

int main() {

	int i;

	GC_INIT();

	FiFoList * list = (FiFoList *) GC_MALLOC(sizeof(FiFoList));

	FiFoListNode * node = (FiFoListNode *)GC_MALLOC(sizeof(FiFoList)); 	

	int j = 12345;
	node->data = &j;

	fifo_list_push(list, node);

	//pop
	FiFoListNode * pop_node = fifo_list_pop(list);

	printf("pop_node value %d\n", *((int *)pop_node->data));
	
	return 0;

	lua_State *lstate = luaL_newstate();

	luaL_openlibs(lstate);

//	for (i = 0; i < 10000000; ++i) {
//
//		int **p = (int **) GC_MALLOC(sizeof(int *));
//		int *q = (int *) GC_MALLOC_ATOMIC(sizeof(int));
//		assert(*p == 0);
//		*p = (int *) GC_REALLOC(q, 2 * sizeof(int));
//		if (i%10000 == 0)
//			printf("Heap size = %d\n", GC_get_heap_size());
//	}
//
//	return 0;
	
		

	int result = load_lua_file(lstate, "test.lua");	

	assert(result == 0);

	call_lua_function_no_args(lstate, "hello_lua");

	lua_close(lstate);
	printf("hello world\n");
	return 0;
}

int pop_lua_error(lua_State *L) {

	printf("%s\n", lua_tostring(L, lua_gettop(L)));
	lua_pop(L, 1);

	return 0;
}

int load_lua_file(lua_State *L, const char* filename) {

	int top = lua_gettop(L);

	int load_result = luaL_loadfile(L, filename);

	if (load_result) {
		
		pop_lua_error(L);
		return 1;	
	}	

	int pcall_result = lua_pcall(L, 0, LUA_MULTRET, 0);

	if (pcall_result) {

		pop_lua_error(L);
		return 1;
	}

	// remove return values
	lua_settop(L, top);
	
	return 0;
}	

int eval_lua_express(lua_State *L, const char* express) {

}

int call_lua_function_no_args(lua_State *L, const char* fname) {
	
	int top = lua_gettop(L);
	
	lua_getfield(L, LUA_GLOBALSINDEX, fname);
	if (lua_pcall(L, 0, LUA_MULTRET, 0)) {
		pop_lua_error(L);
		return 1;
	}

	lua_settop(L, top);

	return 0;
}

