/*
    __ _____ _____ _____
 __|  |   __|     |   | |  JSON for Modern C++ (test suite)
|  |  |__   |  |  | | | |  version 2.0.2
|_____|_____|_____|_|___|  https://github.com/nlohmann/json

Licensed under the MIT License <http://opensource.org/licenses/MIT>.
Copyright (c) 2013-2016 Niels Lohmann <http://nlohmann.me>.

Permission is hereby  granted, free of charge, to any  person obtaining a copy
of this software and associated  documentation files (the "Software"), to deal
in the Software  without restriction, including without  limitation the rights
to  use, copy,  modify, merge,  publish, distribute,  sublicense, and/or  sell
copies  of  the Software,  and  to  permit persons  to  whom  the Software  is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE  IS PROVIDED "AS  IS", WITHOUT WARRANTY  OF ANY KIND,  EXPRESS OR
IMPLIED,  INCLUDING BUT  NOT  LIMITED TO  THE  WARRANTIES OF  MERCHANTABILITY,
FITNESS FOR  A PARTICULAR PURPOSE AND  NONINFRINGEMENT. IN NO EVENT  SHALL THE
AUTHORS  OR COPYRIGHT  HOLDERS  BE  LIABLE FOR  ANY  CLAIM,  DAMAGES OR  OTHER
LIABILITY, WHETHER IN AN ACTION OF  CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE  OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include "catch.hpp"

#include "json.hpp"
using nlohmann::json;

TEST_CASE("deserialization")
{
    SECTION("successful deserialization")
    {
        SECTION("stream")
        {
            std::stringstream ss;
            ss << "[\"foo\",1,2,3,false,{\"one\":1}]";
            json j = json::parse(ss);
            CHECK(j == json({"foo", 1, 2, 3, false, {{"one", 1}}}));
        }

        SECTION("string")
        {
            json::string_t s = "[\"foo\",1,2,3,false,{\"one\":1}]";
            json j = json::parse(s);
            CHECK(j == json({"foo", 1, 2, 3, false, {{"one", 1}}}));
        }

        SECTION("operator<<")
        {
            std::stringstream ss;
            ss << "[\"foo\",1,2,3,false,{\"one\":1}]";
            json j;
            j << ss;
            CHECK(j == json({"foo", 1, 2, 3, false, {{"one", 1}}}));
        }

        SECTION("operator>>")
        {
            std::stringstream ss;
            ss << "[\"foo\",1,2,3,false,{\"one\":1}]";
            json j;
            ss >> j;
            CHECK(j == json({"foo", 1, 2, 3, false, {{"one", 1}}}));
        }

        SECTION("user-defined string literal")
        {
            CHECK("[\"foo\",1,2,3,false,{\"one\":1}]"_json == json({"foo", 1, 2, 3, false, {{"one", 1}}}));
        }
    }

    SECTION("successful deserialization")
    {
        SECTION("stream")
        {
            std::stringstream ss;
            ss << "[\"foo\",1,2,3,false,{\"one\":1}";
            CHECK_THROWS_AS(json::parse(ss), std::invalid_argument);
            CHECK_THROWS_WITH(json::parse(ss), "parse error - unexpected end of input");
        }

        SECTION("string")
        {
            json::string_t s = "[\"foo\",1,2,3,false,{\"one\":1}";
            CHECK_THROWS_AS(json::parse(s), std::invalid_argument);
            CHECK_THROWS_WITH(json::parse(s), "parse error - unexpected end of input; expected ']'");
        }

        SECTION("operator<<")
        {
            std::stringstream ss;
            ss << "[\"foo\",1,2,3,false,{\"one\":1}";
            json j;
            CHECK_THROWS_AS(j << ss, std::invalid_argument);
            CHECK_THROWS_WITH(j << ss, "parse error - unexpected end of input");
        }

        SECTION("operator>>")
        {
            std::stringstream ss;
            ss << "[\"foo\",1,2,3,false,{\"one\":1}";
            json j;
            CHECK_THROWS_AS(ss >> j, std::invalid_argument);
            CHECK_THROWS_WITH(ss >> j, "parse error - unexpected end of input");
        }

        SECTION("user-defined string literal")
        {
            CHECK_THROWS_AS("[\"foo\",1,2,3,false,{\"one\":1}"_json, std::invalid_argument);
            CHECK_THROWS_WITH("[\"foo\",1,2,3,false,{\"one\":1}"_json,
                              "parse error - unexpected end of input; expected ']'");
        }
    }
}
