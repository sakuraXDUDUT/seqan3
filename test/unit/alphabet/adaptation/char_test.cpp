// ==========================================================================
//                 SeqAn - The Library for Sequence Analysis
// ==========================================================================
//
// Copyright (c) 2006-2017, Knut Reinert, FU Berlin
// Copyright (c) 2016-2017, Knut Reinert & MPI Molekulare Genetik
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
//     * Redistributions of source code must retain the above copyright
//       notice, this list of conditions and the following disclaimer.
//     * Redistributions in binary form must reproduce the above copyright
//       notice, this list of conditions and the following disclaimer in the
//       documentation and/or other materials provided with the distribution.
//     * Neither the name of Knut Reinert or the FU Berlin nor the names of
//       its contributors may be used to endorse or promote products derived
//       from this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL KNUT REINERT OR THE FU BERLIN BE LIABLE
// FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
// DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
// SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
// CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
// LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
// OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH
// DAMAGE.
//
// ==========================================================================

#include <iostream>

#include <gtest/gtest.h>

#include <seqan3/alphabet/adaptation/all.hpp>

using namespace seqan3;

template <typename T>
class char_adaptation : public ::testing::Test
{};

using char_types = ::testing::Types<char, char16_t, char32_t>;

TYPED_TEST_CASE(char_adaptation, char_types);

TYPED_TEST(char_adaptation, underlying_char_t)
{
    EXPECT_TRUE((std::is_same_v<underlying_char_t<TypeParam>, TypeParam>));
}

TYPED_TEST(char_adaptation, to_char)
{
    TypeParam l{'A'};
    EXPECT_TRUE((std::is_same_v<decltype(to_char(l)), underlying_char_t<TypeParam>>));
    EXPECT_TRUE((std::is_same_v<decltype(to_char(TypeParam{'A'})), underlying_char_t<TypeParam>>));
    EXPECT_EQ(to_char(TypeParam{'A'}), l);
}

TYPED_TEST(char_adaptation, assign_char)
{
    TypeParam l{'A'};
    EXPECT_TRUE((std::is_same_v<decltype(assign_char(l, 'A')), underlying_char_t<TypeParam> &>));
    EXPECT_TRUE((std::is_same_v<decltype(assign_char(TypeParam{'A'}, 'A')), underlying_char_t<TypeParam> &&>));
    EXPECT_EQ((assign_char(TypeParam{'C'}, 'A')), l);
    EXPECT_EQ((assign_char(l, 'C')), TypeParam{'C'});
}

TYPED_TEST(char_adaptation, underlying_rank_t)
{
    EXPECT_TRUE((std::is_integral_v<underlying_rank_t<TypeParam>>));
    EXPECT_TRUE((std::is_unsigned_v<underlying_rank_t<TypeParam>>));
    EXPECT_GE(sizeof(underlying_rank_t<TypeParam>), sizeof(TypeParam));
}

TYPED_TEST(char_adaptation, to_rank)
{
    TypeParam l{'A'};
    EXPECT_TRUE((std::is_same_v<decltype(to_rank(l)), underlying_rank_t<TypeParam>>));
    EXPECT_TRUE((std::is_same_v<decltype(to_rank(TypeParam{'A'})), underlying_rank_t<TypeParam>>));
    if constexpr (std::is_unsigned_v<TypeParam>)
    {
        unsigned char cmp{'A'};
        EXPECT_EQ(to_rank(TypeParam{65}), cmp);
    }
    else
    {
        EXPECT_EQ(to_rank(TypeParam{65}), 'A');
    }
}

TYPED_TEST(char_adaptation, assign_rank)
{
    TypeParam l{'A'};
    EXPECT_TRUE((std::is_same_v<decltype(assign_rank(l, 65)), underlying_char_t<TypeParam> &>));
    EXPECT_TRUE((std::is_same_v<decltype(assign_rank(TypeParam{'A'}, 65)), underlying_char_t<TypeParam> &&>));
    EXPECT_EQ((assign_rank(TypeParam{'C'}, 65)), l);
    EXPECT_EQ((assign_rank(l, 67)), TypeParam{'C'});
}

TYPED_TEST(char_adaptation, alphabet_size_v)
{
    std::cout << alphabet_size_v<TypeParam> << '\n';
    EXPECT_EQ(alphabet_size_v<TypeParam>,
        static_cast<size_t>(std::numeric_limits<TypeParam>::max()) + 1 - std::numeric_limits<TypeParam>::lowest());
}
