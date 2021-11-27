#include <iostream>
#include <string>
#include <vector>
#include "absl/strings/str_join.h"
#include "absl/algorithm/algorithm.h"
#include "absl/random/random.h"

int main() {

    absl::BitGen bitgen;
    absl::Uniform(bitgen, 0,1);
    
    std::vector<std::string> v = {"foo","bar","baz"};
    std::string s = absl::StrJoin(v, "-");

    std::cout << "Joined string: " << s << "\n";
}
