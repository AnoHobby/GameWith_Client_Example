#if defined(__INTELLISENSE__)
#include "http.cpp";//github.com/anohobby/Cpp_Http_Library
#else
import http;
#endif
int main() {
	http::Client client(L"https://gamewith.jp/gamedb/bbs/game/posts/create");
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
	{"from_platform","ios"},
	{"platform_directory_name",""},
	{"user_name","NAME"},//empty->default name
	{"body","TEXT"},
	{"file",""},
	{"pre_image_path",""},
	{"game_id","0000"},//game id,example->https://gamewith.jp/gamedb/bbs/game/show/0000
	{"mojolicious_csrf_token",""},

	};
	client.request<http::methods::POST>(header,body.to_string());
	return 0;
}
