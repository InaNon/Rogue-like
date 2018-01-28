#include "unitdata.h"


void UnitData::SetData(vector<string> data, int m_graph_handle, vector<string> data_name) {

	int graph_size_x;
	int graph_size_y;
	int graph_chip_x;
	int graph_chip_y;

	GetGraphSize(m_graph_handle, &graph_size_x, &graph_size_y);

	graph_chip_x = graph_size_x / 6;
	graph_chip_y = graph_size_y / 4;

	for (int i = 0; i < 3; i++) {
		graph_handle[DIR_UP - DIR_UP][i] = DerivationGraph(graph_chip_x * i, graph_chip_y * 3, graph_chip_x, graph_chip_y, m_graph_handle);
		graph_handle[DIR_UP_RIGHT - DIR_UP][i] = DerivationGraph(graph_chip_x * (3 + i), graph_chip_y * 3, graph_chip_x, graph_chip_y, m_graph_handle);
		graph_handle[DIR_RIGHT - DIR_UP][i] = DerivationGraph(graph_chip_x * i, graph_chip_y * 2, graph_chip_x, graph_chip_y, m_graph_handle);
		graph_handle[DIR_DOWN_RIGHT - DIR_UP][i] = DerivationGraph(graph_chip_x * (3 + i), graph_chip_y * 1, graph_chip_x, graph_chip_y, m_graph_handle);
		graph_handle[DIR_DOWN - DIR_UP][i] = DerivationGraph(graph_chip_x * i, graph_chip_y * 0, graph_chip_x, graph_chip_y, m_graph_handle);
		graph_handle[DIR_DOWN_LEFT - DIR_UP][i] = DerivationGraph(graph_chip_x * (3 + i), graph_chip_y * 0, graph_chip_x, graph_chip_y, m_graph_handle);
		graph_handle[DIR_LEFT - DIR_UP][i] = DerivationGraph(graph_chip_x * i, graph_chip_y * 1, graph_chip_x, graph_chip_y, m_graph_handle);
		graph_handle[DIR_UP_LEFT - DIR_UP][i] = DerivationGraph(graph_chip_x * (3 + i), graph_chip_y * 2, graph_chip_x, graph_chip_y, m_graph_handle);
	}


	for (unsigned int j = 0; j < size(data_name); j++) {
		if (data_name[j] == "name")
			name = data[j];
		else if (data_name[j] == "explain")
			explain = data[j];
		else if (data_name[j] == "spown_dungeon")
			dungeon_kind = (DUNGEON_KIND)stoi(data[j]);
		else if (data_name[j] == "max_hp")
			max_hp = stoi(data[j]);
		else if (data_name[j] == "atk")
			atk = stoi(data[j]);
		else if (data_name[j] == "def")
			def = stoi(data[j]);
		else if (data_name[j] == "speed")
			speed = stoi(data[j]);
		else if (data_name[j] == "luk")
			luk = stoi(data[j]);
		else if (data_name[j] == "exp")
			exp = stoi(data[j]);
		else if (data_name[j] == "delta_max_hp")
			delta_max_hp = stoi(data[j]);
		else if (data_name[j] == "delta_atk")
			delta_atk = stoi(data[j]);
		else if (data_name[j] == "delta_def")
			delta_def = stoi(data[j]);
		else if (data_name[j] == "delta_speed")
			delta_speed = stoi(data[j]);
		else if (data_name[j] == "delta_luk")
			delta_luk = stoi(data[j]);
		else if (data_name[j] == "delta_exp")
			delta_exp = stoi(data[j]);
		else if (data_name[j] == "growth_floor")
			growth_floor = stoi(data[j]);
		else if (data_name[j] == "peak_floor")
			peak_floor = stoi(data[j]);
		else if (data_name[j] == "decay_floor")
			decay_floor = stoi(data[j]);
		else if (data_name[j] == "growth_epidemicity")
			growth_epidemicity = stoi(data[j]);
		else if (data_name[j] == "peak_epidemicity")
			peak_epidemicity = stoi(data[j]);
		else if (data_name[j] == "decay_epidemicity")
			decay_epidemicity = stoi(data[j]);

	}
}

int UnitData::GetDrawGraphHandle(DIRECTION direction, int pose) {

	return graph_handle[direction - DIR_UP][pose];
}

void UnitData::PrintUnitData() {

	printfDx("%s:%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d", name.c_str(), dungeon_kind, delta_max_hp, delta_atk, delta_def, delta_speed, delta_luk, delta_exp,growth_floor, peak_floor, decay_floor, growth_epidemicity, peak_epidemicity, decay_epidemicity);
}

int UnitData::GetStatus(STATUS status_index) {

	switch (status_index) {

	case (MAX_HP):
		return max_hp;
		break;

	case(DELTA_MAX_HP):
		return delta_max_hp;
		break;

	case(ATK):
		return atk;
		break;

	case(DELTA_ATK):
		return delta_atk;
		break;

	case(DEF):
		return def;
		break;

	case(DELTA_DEF):
		return delta_def;
		break;

	case(SPEED):
		return speed;
		break;

	case(DELTA_SPEED):
		return delta_speed;
		break;

	case(LUK):
		return luk;
		break;

	case(DELTA_LUK):
		return delta_luk;
		break;

	case(EXP):
		return exp;
		break;

	case(DELTA_EXP):
		return delta_exp;
		break;
	}

	return -999;

}

UnitData::UnitData() {
	max_hp = 0;
	atk = 0;
	def = 0;
	speed = 0;
	luk = 0;
	exp = 0;
	delta_max_hp = 0;
	delta_atk = 0;
	delta_def = 0;
	delta_speed = 0;
	delta_luk = 0;
	delta_exp = 0;
	dungeon_kind = FOREST;

}
UnitData::~UnitData() {}
