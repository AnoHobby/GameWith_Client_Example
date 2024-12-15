#if defined(__INTELLISENSE__)
#include "http.cpp";//github.com/anohobby/Cpp_Http_Library
#else
import http;
#endif
#include <iostream>
int main() {
	http::Client client(L"https://gamewith.jp/gamedb/bbs/game/show/0000");//0000->game id
	const auto html = client.request<http::methods::GET>().read_content();
	const auto symbol = std::string_view("data-number=\"");
	const auto number=html.find(symbol)+symbol.size();
	std::cout<<html.substr(number, html.find_first_of("\"", number)-number);
	return 0;
}