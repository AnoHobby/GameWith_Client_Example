#if defined(__INTELLISENSE__)
#include "http.cpp";//github.com/anohobby/Cpp_Http_Library
#else
import http;
#endif
#include <iostream>
int main() {
	http::Client client(L"https://gamewith.jp/api/search/bbs/game/report");
	http::Header header{
	{L"Content-Type",L"application/x-www-form-urlencoded"},
	{L"cookie",
	http::Cookie{
			{L"mojolicious_csrf_token",L""},
			{L"post_rule",L"4nK5VjZU_u11hm36naduQdp9CVkpPD9cDZKpXI7z8ulMTTVtTE10ejFkNE83bFNSV3NVVWhQMWRjMFF0ZlhDRHpKQzRJTWdBZUVr"}//example
		}.to_string()
	}
	};
	http::Form_Url_Encoded body{
		{"game_id","0000"},//game id
		{"number","00000"},//reply number.example >>00000
		{"mojolicious_csrf_token",""},
	};
	std::cout<<client.request<http::methods::POST>(header, body.to_string()).read_content();
	return 0;
}