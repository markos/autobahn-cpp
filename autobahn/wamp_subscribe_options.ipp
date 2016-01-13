///////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) Tavendo GmbH
//
// Boost Software License - Version 1.0 - August 17th, 2003
//
// Permission is hereby granted, free of charge, to any person or organization
// obtaining a copy of the software and accompanying documentation covered by
// this license (the "Software") to use, reproduce, display, distribute,
// execute, and transmit the Software, and to prepare derivative works of the
// Software, and to permit third-parties to whom the Software is furnished to
// do so, all subject to the following:
//
// The copyright notices in the Software and this entire statement, including
// the above license grant, this restriction and the following disclaimer,
// must be included in all copies of the Software, in whole or in part, and
// all derivative works of the Software, unless such copies or derivative
// works are solely in the form of machine-executable object code generated by
// a source language processor.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
// SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
// FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
// ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
// DEALINGS IN THE SOFTWARE.
//
///////////////////////////////////////////////////////////////////////////////

#include <msgpack.hpp>
#include <string>
#include <unordered_map>

namespace autobahn {

inline wamp_subscribe_options::wamp_subscribe_options()
    : m_match()
{
}

inline const std::string& wamp_subscribe_options::match() const
{
    return *m_match;
}

inline const bool wamp_subscribe_options::is_match_set() const
{
    return m_match.is_initialized();
}

inline void wamp_subscribe_options::set_match(const std::string& match)
{
    if (!(match == "exact" || match == "prefix" || match == "wildcard"))
    {
        throw std::runtime_error("The value of 'match' must be 'exact', 'prefix', or 'wildcard'.");
    }
    m_match = match;
}

} // namespace autobahn

namespace msgpack {
MSGPACK_API_VERSION_NAMESPACE(MSGPACK_DEFAULT_API_NS) {
namespace adaptor {

template<>
struct convert<autobahn::wamp_subscribe_options>
{
    msgpack::object const& operator()(
            msgpack::object const& object,
            autobahn::wamp_subscribe_options& options) const
    {
        return object;
    }
};

template<>
struct pack<autobahn::wamp_subscribe_options>
{
    template <typename Stream>
    msgpack::packer<Stream>& operator()(
            msgpack::packer<Stream>& packer,
            autobahn::wamp_subscribe_options const& options) const
    {
        std::map<std::string, std::string> options_map;
        bool should_pack_options = false;

        if (options.is_match_set())
        {
            options_map["match"] = options.match();
            should_pack_options = true;
        }

        if (should_pack_options)
        {
            packer.pack(options_map);
        }
        else
        {
            packer.pack_map(0);
        }

        return packer;
    }
};

template <>
struct object_with_zone<autobahn::wamp_subscribe_options>
{
    void operator()(
            msgpack::object::with_zone& object,
            const autobahn::wamp_subscribe_options& options)
    {
        std::map<std::string, std::string> options_map;
        bool should_copy_options = false;

        if (options.is_match_set())
        {
            options_map["match"] = options.match();
            should_copy_options = true;
        }

        if (should_copy_options)
        {
            object << options_map;
        }
    }
};

} // namespace adaptor
} // MSGPACK_API_VERSION_NAMESPACE(MSGPACK_DEFAULT_API_NS)
} // namespace msgpack

