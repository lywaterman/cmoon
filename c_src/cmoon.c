#include <erl_nif.h>

int erl_lua_num_to_num(ErlNifEnv *env, ERL_NIF_TERM term) {

	int32_t i32;
	if (enif_get_int(env, term, &i32)) {
		// todu
	}

	int64_t i64;
	if (enif_get_int64(env, term, &i64)) {
			
	}

	double db;
	if (enif_get_double(env, term, &db)) {

	}

	return 0;
}

int erl_lua_atom_to_string() {

	return 0;

}

int erl_lua_binary_to_string() {

	return 0;

}
