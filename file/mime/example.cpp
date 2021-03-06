// example.cpp
//
// MIT License
//
// Copyright (c) 2017 Heikki Hellgren <heiccih@gmail.com>
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#include "detector.hpp"
#include <fstream>
#include <iostream>

using namespace drodil::file::mime;

int main(int argc, char** argv) {
	if (argc <= 1) {
		std::cout << "Pass filename." << std::endl;
		return 0;
	}

	std::fstream file(argv[1], std::ios::in | std::ios::binary | std::ios::ate);
	if (!file || !file.is_open()) {
		std::cout << "Could not open given file " << argv[1] << std::endl;
		return 1;
	}

	Detector det;
	std::cout << "From fstream: " << det.detect(file) << std::endl;
	file.close();

	std::cout << "From extension: " << det.detect(std::string(argv[1]))
			<< std::endl;
}

