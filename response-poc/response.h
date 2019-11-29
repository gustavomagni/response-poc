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

#pragma once
class response : public proton::messaging_handler {

	std::string conn_url_;
	std::string addr_;
	proton::connection conn_;
	std::map<std::string, proton::sender> senders_;

public:	response(const std::string& u, const std::string& a) : conn_url_(u), addr_(a) {}

	  void on_container_start(proton::container& c) override {
		  conn_ = c.connect(conn_url_);
		  conn_.open_receiver(addr_);
		  std::cout << "Server connected to " << conn_url_ << std::endl;
	  }

	 
	  void on_message(proton::delivery&, proton::message& m) override {
		  std::cout << "Received " << m.body() << std::endl;
		  std::string reply_to = m.reply_to();
		  proton::message reply;
		  reply.to(reply_to);
		  reply.body(m.body());
		  reply.correlation_id(m.correlation_id());

		  if (!senders_[reply_to]) {
			  senders_[reply_to] = conn_.open_sender(reply_to);
		  }

		  senders_[reply_to].send(reply);
	  }
};

