#if defined(__INTELLISENSE__)
#include "http.cpp";//github.com/anohobby/Cpp_Http_Library
#else
import http;
#endif
#include <string_view>
auto extract_content(const auto& text,const std::string_view start_delimiter,const std::string_view end_delimiter) {
	const auto number = text.find(start_delimiter) + start_delimiter.size();
	return std::move(text.substr(number, text.find_first_of(end_delimiter, number) - number));
}
int main() {

	http::Client login_client(L"https://gamewith.jp/user/login");
	http::Client post_client(L"https://gamewith.jp/gamedb/bbs/game/posts/create");
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

	const auto html = login_client.request<http::methods::GET>(account_header).read_content();

	http::Form_Url_Encoded post_body{
		{"from_platform","ios"},
		{"platform_directory_name",""},
		{"user_name",""},
		{"login_user_name",extract_content(html,"<p class=\"_name _is-cell\">","<")},//empty->default name,It is OK even if it differs from the registered information
		//You can change the name freely, but in this example, it will be obtained from existing information.
		{"user_id",extract_content(html,"loginUserId: \"","\"")},//user id
		//find from
		//loginUserId: "0000"
		// or
		//https://gamewith.jp/user/profile/0000"
		{"use-profile","1"},
		{"body","TEXT"},
		{"file",""},
		{"pre_image_path",""},
		{"game_id","0000"},//game id
		{"mojolicious_csrf_token",""},
	};
	post_client.request<http::methods::POST>(account_header, post_body.to_string());
	return 0;
}