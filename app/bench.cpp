#include <benchmark/benchmark.h>
#include <fstream>
#include <fstream>
#include <ios>
#include <iostream>
#include <string>
#include <algorithm>
#include <map>
#include <unordered_map>


static void BM_StringCreation(benchmark::State& state) {
  for (auto _ : state)
    std::string empty_string;
}
// Register the function as a benchmark
BENCHMARK(BM_StringCreation);

template<typename T>
T prepare_test_data(int default_)
{
    T names_buffer;
    auto file = std::ifstream("names.txt");
    std::string name;
    while (std::getline(file, name))
        names_buffer[name] = default_;
    return names_buffer;
}
std::vector<std::string> prepare_test_data()
{
    std::vector<std::string> names_buffer;
    names_buffer.reserve(1000);
    auto file = std::ifstream("names.txt");
    std::string name;
    while (std::getline(file, name))
        names_buffer.push_back(name);
    return names_buffer;
}

template<typename T>
void add_unique(T& cont_, const std::string& name_)
{
    if (std::find(cont_.begin(), cont_.end(), name_) == cont_.end())
        cont_.push_back(name_);
}

template<>
void add_unique(std::set<std::string>& cont_, const std::string& name_) 
{
    cont_.insert(name_);
}

template<typename T>
static void BM_AddNonDuplicatesToContainer(benchmark::State& state)
{
    auto names_buffer = prepare_test_data();
    T container;
    for (auto _ : state)
        for (auto& name : names_buffer)
            add_unique<T>(container, name);

}

template<typename T>
static void BM_IndexLookUp(benchmark::State& state)
{
    auto data = prepare_test_data<T>(1);
    std::string lookup = "njlcdnjl";
    for (auto _ : state)
    {
        auto& ref = data[lookup];
        if(ref == 1)
            data.erase(lookup);                           
        else
            ref = 1;
    }
}

template<typename T>
static void BM_FindLookUp(benchmark::State& state)
{
    auto data = prepare_test_data<T>(1);
    std::string lookup = "njlcdnjl";
    for (auto _ : state)
    {
        auto ref = data.find(lookup);
        if(ref != data.end()) 
            data.erase(lookup);                           
        else
           data.emplace(lookup,1);
    }
}

// Define another benchmark
static void BM_StringCopy(benchmark::State& state) {
  std::string x = "hello";
  for (auto _ : state)
    std::string copy(x);
}

BENCHMARK_TEMPLATE(BM_AddNonDuplicatesToContainer, std::set<std::string>);
BENCHMARK_TEMPLATE(BM_AddNonDuplicatesToContainer, std::vector<std::string>);
BENCHMARK_TEMPLATE(BM_FindLookUp, std::unordered_map<std::string, int>);
BENCHMARK_TEMPLATE(BM_IndexLookUp, std::unordered_map<std::string, int>);
BENCHMARK_TEMPLATE(BM_FindLookUp, std::map<std::string, int>);
BENCHMARK_TEMPLATE(BM_IndexLookUp, std::map<std::string, int>);
BENCHMARK(BM_StringCopy);

BENCHMARK_MAIN();
