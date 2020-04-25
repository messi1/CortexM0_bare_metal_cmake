#pragma once

template<typename addr_type, typename reg_type, const addr_type port, const reg_type bpos>
class port_pin
{
public:
    static void set_direction_output()
    {
        // Set the port pin direction to output.
        port_dir_type::bit_set();
    }
    static void set_direction_input()
    {
        // Set the port pin direction to input.
        port_dir_type::bit_clr();
    }
        static void set_pin_high()
    {
        // Set the port output value to high.
        port_pin_type::bit_set();
    }
        static void set_pin_low()
    {
        // Set the port output value to low.
        port_pin_type::bit_clr();
    }

    static bool read_input_value()
    {
        // Read the port input value.
        port_inp_type::bit_get();
    }

    static void toggle()
    {
        // Toggle the port output value.
        port_pin_type::bit_not();
    }
    private:
        static constexpr addr_type pdir = port - 1U;
        static constexpr addr_type pinp = port - 2U;
        // Type definition of the port data register.
        typedef reg_access<addr_type, reg_type, port, bpos> port_pin_type;
        // Type definition of the port direction register.
        typedef reg_access<addr_type, reg_type, pdir, bpos> port_dir_type;
        // Type definition of the port input register.
        typedef reg_access<addr_type, reg_type, pinp, bpos> port_inp_type;
};
