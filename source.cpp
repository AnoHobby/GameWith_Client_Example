#if defined(__INTELLISENSE__)
#include "http.cpp";
#else
import http;
#endif
int main() {
	http::Client login_client(L"https://gamewith.jp/user/login");
	http::Client post_client(L"https://gamewith.jp/gamedb/bbs/game/posts/create");
	http::Header anonymous_header{
	{L"Content-Type",L"application/x-www-form-urlencoded"},
	{L"cookie",
	http::Cookie{
			{L"mojolicious_csrf_token",L""},
			{L"post_rule",L"4nK5VjZU_u11hm36naduQdp9CVkpPD9cDZKpXI7z8ulMTTVtTE10ejFkNE83bFNSV3NVVWhQMWRjMFF0ZlhDRHpKQzRJTWdBZUVr"}//example
		}.to_string()
	}
	};
	http::Form_Url_Encoded anonymous_post_body{
	{"from_platform","ios"},
	{"platform_directory_name",""},
	{"user_name","NAME"},//empty->default name
	{"body","TEXT"},
	{"file",""},
	{"pre_image_path",""},
	{"game_id","0000"},//game id,example->https://gamewith.jp/gamedb/bbs/game/show/0000
	{"mojolicious_csrf_token",""},

	};
	auto response = login_client.request<http::methods::GET>();
	auto fuelmid = response.query_cookies()[2];
	const auto separator = fuelmid.find_first_of(L'=');
	http::Header account_header{
	{L"Content-Type",L"application/x-www-form-urlencoded"},
	{L"cookie",
	http::Cookie{
			{fuelmid.substr(0,separator),fuelmid.substr(separator + 1,fuelmid.find_first_of(L';') - separator - 1)},
			{L"mojolicious_csrf_token",L""},
			{L"post_rule",L"4nK5VjZU_u11hm36naduQdp9CVkpPD9cDZKpXI7z8ulMTTVtTE10ejFkNE83bFNSV3NVVWhQMWRjMFF0ZlhDRHpKQzRJTWdBZUVr"}//example
		}.to_string()
	}
	};
	http::Form_Url_Encoded account_body{
		{"username","YOUR_MAIL_ADDRESS"},
		{"password","YOUR_PASSWORD"},
		{"mojolicious_csrf_token",""},
		{"force",""},
		{"is_skyflag","0"},
		{"redirect_path","null"},
		{"login",""}

	};
	login_client.request<http::methods::POST>(account_header, std::move(account_body.to_string())).query_header();
	http::Form_Url_Encoded post_body{
		{"from_platform","ios"},
		{"platform_directory_name",""},
		{"user_name",""},
		{"login_user_name","NAME"},//empty->default name
		{"user_id","0"},//user id
		{"use-profile","1"},
		{"body","TEXT"},
		{"file",""},
		{"pre_image_path",""},
		{"game_id","0000"},
		{"mojolicious_csrf_token",""},

	};
	post_client.request<http::methods::POST>(account_header,post_body.to_string());
	return 0;
}
