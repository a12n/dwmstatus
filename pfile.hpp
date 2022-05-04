#ifndef DWMSTATUS_PFILE_HPP
#define DWMSTATUS_PFILE_HPP

#include "config.hpp"
#include "decl.hpp"

namespace dwmstatus {

class pfile
{
public:
    explicit
    pfile(const string& filename)
    {
        f.rdbuf()->pubsetbuf(nullptr, 0);
        f.exceptions(ifstream::failbit);
        f.open(filename);
    }

    pfile(const pfile&) = delete;

    pfile(pfile&&) = default;

    pfile&
    operator=(const pfile&) = delete;

    pfile&
    operator=(pfile&&) = default;

    template <class T>
    T
    read()
    {
        f.seekg(0);
        T ans;
        f >> ans;
        return ans;
    }

    template <typename T>
    optional<T>
    read_value()
    {
        return dwmstatus::read_value<T>(f);
    }

    pfile&
    rewind()
    {
        f.seekg(0);
        return *this;
    }

private:
    ifstream f;
};

} // namespace dwmstatus

#endif  // DWMSTATUS_PFILE_HPP
