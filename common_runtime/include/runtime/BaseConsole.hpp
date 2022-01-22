#ifndef ELROND_COMMON_RUNTIME_RUNTIME_BASE_CONSOLE_HPP
    #define ELROND_COMMON_RUNTIME_RUNTIME_BASE_CONSOLE_HPP

    #include <elrond.hpp>

    namespace elrond
    {
        namespace runtime
        {
            class BaseConsole : public elrond::interface::Console
            { 
                protected:
                    virtual void printInfo(const elrond::StreamH& handle) const =0;
                    virtual void throwError(const elrond::StreamH& handle) const =0;
    
                public:

                    virtual ~BaseConsole() = ELROND_DEFAULT_DESTRUCTOR;

                    //
                    // Stream handle
                    //
                    void info(const elrond::StreamH& handle) const override;
                    void error(const elrond::StreamH& handle) const override;

                    //
                    // Char and strings
                    //
                    void info(const char c) const override;
                    void info(const unsigned char c) const override;
                    void info(const char c[]) const override;
                    void info(elrond::string str) const override;
                    void error(const char c[]) const override;
                    void error(elrond::string str) const override;

                    //
                    // Numeric
                    //
                    void info(const int i) const override;
                    void info(const unsigned int i) const override;
                    void info(const long l) const override;
                    void info(const unsigned long l) const override;
                    void info(const double d) const override;
            };
        }
    }

#endif
