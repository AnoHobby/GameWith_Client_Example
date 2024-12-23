#if defined(__INTELLISENSE__)
#include "http.cpp";//github.com/anohobby/Cpp_Http_Library
#else
import http;
#endif
int main() {
	http::Client client(L"https://gamewith.jp/api/userreview/evaluate_useful");
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
	{"game_id","0000"},//game id,example->https://gamewith.jp/gamedb/bbs/game/show/0000
	{"user_id","000000"},//id of person who reviewd
	{"mojolicious_csrf_token",""},

	};
	client.request<http::methods::POST>(header, body.to_string()).read_content();
	return 0;
}