#pragma once
#include <memory>
#include <string>
#include <vector>
class State;
class Route {
public:
	std::shared_ptr<State> start;
	std::shared_ptr<State> end;
};

class State {
public:
	//状态名
	std::string stateName="";
	//状态可切换的路径
	std::vector<std::string> routes;
};


class StateMachine {

public:
	//注册状态
	bool RegisterState(std::shared_ptr<State> state);
	//注销状态
	bool DestroyState(std::shared_ptr<State> state);
	bool DestroyState(std::string state);


};