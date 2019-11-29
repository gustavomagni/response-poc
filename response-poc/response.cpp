/*
 *
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied.  See the License for the
 * specific language governing permissions and limitations
 * under the License.
 *
 */
#include <proton/connection.hpp>
#include <proton/container.hpp>
#include <proton/message.hpp>
#include <proton/message_id.hpp>
#include <proton/messaging_handler.hpp>
#include <iostream>
#include <map>
#include <string>
#include <cctype>
#include "fake_cpp11.h"
#include "response.h"

int main(int argc, char** argv) {
	try {
		std::string conn_url = argc > 1 ? argv[1] : "//127.0.0.1:5672";
		std::string addr = argc > 2 ? argv[2] : "examples";
		response resp(conn_url, addr);
		proton::container(resp).run();
		return 0;
	}
	catch (const std::exception & e) {
		std::cerr << e.what() << std::endl;
	}
	return 1;
}
