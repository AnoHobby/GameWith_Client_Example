#if defined(__INTELLISENSE__)
#include "http.cpp";//github.com/anohobby/Cpp_Http_Library
#else
import http;
#endif
#include <iostream>
int main() {
	http::Query_Parameter param{
	{L"game_id",L"0000"},//game id
	{L"number",L"000000"},//>>000000
	};
	http::Client client(L"https://gamewith.jp/api/search/bbs/game/post/show",param.to_string());
	std::cout<<client.request<http::methods::GET>().read_content();
	return 0;
}	
