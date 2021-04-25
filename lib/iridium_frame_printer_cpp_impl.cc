/* -*- c++ -*- */
/*
 * Copyright 2021 gr-iridium author.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include "iridium_frame_printer_cpp_impl.h"
#include <gnuradio/io_signature.h>

#include "iridium.h"

using boost::format;

#include <ctime>

namespace gr {
namespace iridium {

iridium_frame_printer_cpp::sptr iridium_frame_printer_cpp::make(std::string file_info)
{
    return gnuradio::make_block_sptr<iridium_frame_printer_cpp_impl>(file_info);
}


/*
 * The private constructor
 */
iridium_frame_printer_cpp_impl::iridium_frame_printer_cpp_impl(std::string file_info)
    : gr::sync_block("iridium_frame_printer_cpp",
                     gr::io_signature::make(0, 0, 0),
                     gr::io_signature::make(0, 0, 0))
{
    if(file_info == "") {
        d_file_info = "i-" + std::to_string(std::time(nullptr)) + "-t1";
    } else {
        d_file_info = file_info;
    }

    auto port_name = pmt::mp("pdus");
    message_port_register_in(port_name);
    set_msg_handler(port_name, [this](const pmt::pmt_t& msg) { this->handler(msg); });
}

/*
 * Our virtual destructor.
 */
iridium_frame_printer_cpp_impl::~iridium_frame_printer_cpp_impl() {}

void iridium_frame_printer_cpp_impl::handler(const pmt::pmt_t& msg)
{
    pmt::pmt_t symbols = pmt::cdr(msg);
    pmt::pmt_t meta = pmt::car(msg);

    double timestamp = pmt::to_double(pmt::dict_ref(meta, pmt::mp("timestamp"), pmt::PMT_NIL));
    float center_frequency = pmt::to_float(pmt::dict_ref(meta, pmt::mp("center_frequency"), pmt::PMT_NIL));
    float magnitude = pmt::to_float(pmt::dict_ref(meta, pmt::mp("magnitude"), pmt::PMT_NIL));
    float noise = pmt::to_float(pmt::dict_ref(meta, pmt::mp("noise"), pmt::PMT_NIL));
    uint64_t id = pmt::to_uint64(pmt::dict_ref(meta, pmt::mp("id"), pmt::PMT_NIL));
    int confidence = pmt::to_long(pmt::dict_ref(meta, pmt::mp("confidence"), pmt::PMT_NIL));
    float level = pmt::to_float(pmt::dict_ref(meta, pmt::mp("level"), pmt::PMT_NIL));
    int n_symbols = pmt::to_long(pmt::dict_ref(meta, pmt::mp("n_symbols"), pmt::PMT_NIL));

    std::cout << "RAW: " << d_file_info << " ";
    std::cout << format("%012.4f ") % (timestamp*1000);
    std::cout << format("%010d ") % int(center_frequency);
    std::cout << format("N:%05.2f%+06.2f ") % magnitude % noise;
    std::cout << format("I:%011d ") % id;
    std::cout << format("%3d%% ") % confidence;
    std::cout << format("%.5f ") % level;
    std::cout << format("%3d ") % (n_symbols - ::iridium::UW_LENGTH);


    auto bits = pmt::u8vector_elements(symbols);
    for (const auto i: bits) {
        std::cout << std::to_string(i);
    }

    std::cout << std::endl;
}

int iridium_frame_printer_cpp_impl::work(int noutput_items,
                                         gr_vector_const_void_star& input_items,
                                         gr_vector_void_star& output_items)
{
    return 0;
}

} /* namespace iridium */
} /* namespace gr */
