#pragma once
#include <vector>
#include <string>
#include <map>

std::map<std::pair<char, char>, std::map<char, std::string>> adder={
{{'=','='},{{'=',"--"},{'-',"-0"},{'0',"-1"},{'1',"-2"},{'2',"0="}}},
{{'=','-'},{{'=',"-0"},{'-',"-1"},{'0',"-2"},{'1',"0="},{'2',"0-"}}},
{{'=','0'},{{'=',"-1"},{'-',"-2"},{'0',"0="},{'1',"0-"},{'2',"00"}}},
{{'=','1'},{{'=',"-2"},{'-',"0="},{'0',"0-"},{'1',"00"},{'2',"01"}}},
{{'=','2'},{{'=',"0="},{'-',"0-"},{'0',"00"},{'1',"01"},{'2',"02"}}},
{{'-','='},{{'=',"-0"},{'-',"-1"},{'0',"-2"},{'1',"0="},{'2',"0-"}}},
{{'-','-'},{{'=',"-1"},{'-',"-2"},{'0',"0="},{'1',"0-"},{'2',"00"}}},
{{'-','0'},{{'=',"-2"},{'-',"0="},{'0',"0-"},{'1',"00"},{'2',"01"}}},
{{'-','1'},{{'=',"0="},{'-',"0-"},{'0',"00"},{'1',"01"},{'2',"02"}}},
{{'-','2'},{{'=',"0-"},{'-',"00"},{'0',"01"},{'1',"02"},{'2',"1="}}},
{{'0','='},{{'=',"-1"},{'-',"-2"},{'0',"0="},{'1',"0-"},{'2',"00"}}},
{{'0','-'},{{'=',"-2"},{'-',"0="},{'0',"0-"},{'1',"00"},{'2',"01"}}},
{{'0','0'},{{'=',"0="},{'-',"0-"},{'0',"00"},{'1',"01"},{'2',"02"}}},
{{'0','1'},{{'=',"0-"},{'-',"00"},{'0',"01"},{'1',"02"},{'2',"1="}}},
{{'0','2'},{{'=',"00"},{'-',"01"},{'0',"02"},{'1',"1="},{'2',"1-"}}},
{{'1','='},{{'=',"-2"},{'-',"0="},{'0',"0-"},{'1',"00"},{'2',"01"}}},
{{'1','-'},{{'=',"0="},{'-',"0-"},{'0',"00"},{'1',"01"},{'2',"02"}}},
{{'1','0'},{{'=',"0-"},{'-',"00"},{'0',"01"},{'1',"02"},{'2',"1="}}},
{{'1','1'},{{'=',"00"},{'-',"01"},{'0',"02"},{'1',"1="},{'2',"1-"}}},
{{'1','2'},{{'=',"01"},{'-',"02"},{'0',"1="},{'1',"1-"},{'2',"10"}}},
{{'2','='},{{'=',"0="},{'-',"0-"},{'0',"00"},{'1',"01"},{'2',"02"}}},
{{'2','-'},{{'=',"0-"},{'-',"00"},{'0',"01"},{'1',"02"},{'2',"1="}}},
{{'2','0'},{{'=',"00"},{'-',"01"},{'0',"02"},{'1',"1="},{'2',"1-"}}},
{{'2','1'},{{'=',"01"},{'-',"02"},{'0',"1="},{'1',"1-"},{'2',"10"}}},
{{'2','2'},{{'=',"02"},{'-',"1="},{'0',"1-"},{'1',"10"},{'2',"11"}}}};