/*
Copyright (C) 2015-present The DotCpp Authors.

This file is part of .C++, a native C++ implementation of
popular .NET class library APIs developed to facilitate
code reuse between C# and C++.

    http://github.com/dotcpp/dotcpp (source)
    http://dotcpp.org (documentation)

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

   http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/

#include <dot/implement.hpp>
#include <dot/noda_time/LocalDate.hpp>
#include <dot/noda_time/Period.hpp>
#include <dot/noda_time/LocalTime.hpp>
#include <dot/noda_time/LocalDateTime.hpp>
#include <dot/system/object.hpp>
#include <dot/system/string.hpp>

namespace dot
{
    /// <summary>
    /// In C\# local date is a struct, and as all structs it has default constructor
    /// that initializes all backing variables to 0. This means that default
    /// constructed value corresponds to 0001-01-01. As Boost date_time library
    /// does not accept the date 0001-01-01, we will instead use the Unix epoch
    /// 1970-01-01 as default constructed value.
    /// </summary>
    local_date::local_date()
        : gdate(1970, 1, 1)
    {
    }

    /// <summary>Constructs an instance for the given year, month and day in the ISO calendar.</summary>
    local_date::local_date(int year, int month, int day)
        : gdate(year, month, day)
    {}

    /// <summary>Create from Boost gregorian date.</summary>
    local_date::local_date(gdate date)
        : gdate(date)
    {}

    local_date::local_date(const local_date& other)
    {
        *this = other;
    }

    local_date::local_date(object const& rhs) { *this = rhs.operator local_date(); }

    local_date local_date::Add(const local_date& date, const Period& period)
    {
        return date + period;
    }

    LocalDateTime local_date::At(const LocalTime& time) const
    {
        return *this + time;
    }

    LocalDateTime local_date::AtMidnight() const
    {
        return *this + LocalTime(0, 0);
    }

    int local_date::CompareTo(const local_date& other) const
    {
        if (*this == other)
            return 0;

        return *this > other ? 1 : -1;
    }

    bool local_date::equals(const local_date& other) const
    {
        return *this == other;
    }

    string local_date::to_string() const
    {
        boost::posix_time::time_facet* facet = new boost::posix_time::time_facet();
        facet->format("%Y-%m-%d");
        std::stringstream stream;
        stream.imbue(std::locale(std::locale::classic(), facet));
        stream << this->AtMidnight();
        return stream.str();
    }

    Period local_date::Minus(const local_date& date) const
    {
        return *this - date;
    }

    local_date local_date::Minus(const Period& period) const
    {
        return *this - period;
    }

    local_date local_date::Next(int targetDayOfWeek) const
    {
        if (day_of_week() == targetDayOfWeek)
            return PlusWeeks(1);
        auto wd = boost::gregorian::greg_weekday(targetDayOfWeek);
        return boost::gregorian::next_weekday(*this, wd);
    }

    local_date local_date::Plus(const Period& period) const
    {
        return *this + period;
    }

    local_date local_date::PlusDays(int days) const
    {
        return *this + boost::gregorian::days(days);
    }

    local_date local_date::PlusMonths(int months) const
    {
        return *this + boost::gregorian::months(months);
    }

    local_date local_date::PlusWeeks(int weeks) const
    {
        return *this + boost::gregorian::weeks(weeks);
    }

    local_date local_date::PlusYears(int years) const
    {
        return *this + boost::gregorian::years(years);
    }

    local_date local_date::Previous(int targetDayOfWeek) const
    {
        if (day_of_week() == targetDayOfWeek)
            return PlusWeeks(-1);
        auto wd = boost::gregorian::greg_weekday(targetDayOfWeek);
        return boost::gregorian::previous_weekday(*this, wd);
    }

    Period local_date::Subtract(const local_date& lhs, const local_date& rhs)
    {
        return lhs - rhs;
    }

    local_date local_date::Subtract(const local_date& date, const Period& period)
    {
        return date + period;
    }

    LocalDateTime local_date::operator+(const LocalTime& time) const
    {
        return {*this, time};
    }

    local_date local_date::operator+(const Period& period) const
    {
        return static_cast<gdate>(*this) + static_cast<date_duration>(period);
    }

    bool local_date::operator==(const local_date& other) const
    {
        return static_cast<gdate>(*this) == static_cast<gdate>(other);
    }

    bool local_date::operator!=(const local_date& other) const
    {
        return static_cast<gdate>(*this) != static_cast<gdate>(other);
    }

    bool local_date::operator>(const local_date& other) const
    {
        return static_cast<gdate>(*this) > static_cast<gdate>(other);
    }

    bool local_date::operator>=(const local_date& other) const
    {
        return static_cast<gdate>(*this) >= static_cast<gdate>(other);
    }

    bool local_date::operator<(const local_date& other) const
    {
        return static_cast<gdate>(*this) < static_cast<gdate>(other);
    }

    bool local_date::operator<=(const local_date& other) const
    {
        return static_cast<gdate>(*this) <= static_cast<gdate>(other);
    }

    Period local_date::operator-(const local_date& other) const
    {
        return static_cast<gdate>(*this) - static_cast<gdate>(other);
    }

    local_date local_date::operator-(const Period& period) const
    {
        return static_cast<gdate>(*this) - static_cast<date_duration>(period);
    }
}
