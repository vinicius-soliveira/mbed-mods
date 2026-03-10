/*
 * Copyright (C) 2025 CNPEM (cnpem.br)
 * Author: Vinicius Oliveira <vinicius.silva@lnls.br>
 */

#ifndef HTTPCTRLINTFMODULE_HPP_
#define HTTPCTRLINTFMODULE_HPP_

#include "mbed.h"
#include "EthernetInterface.h"
#include "TCPSocket.h"

#include "CtrlIntfModule.hpp"

#define HTTP_BUFFER_SIZE 1024

class HTTPCtrlIntfModule final : public CtrlIntfModule {
  public:
    enum HttpRequestType {
      HTTP_REQ_INVALID = 0,
      HTTP_REQ_GET_ROOT,
      HTTP_REQ_POST_CMD
    };

    HTTPCtrlIntfModule(
        EthernetInterface *p_net,
        uint16_t port,
        int timeout,
        /* CtrlIntfModule params */
        const char terminator,
        const uint8_t max_cmd_len,
        mbed::Callback<bool(Kernel::Clock::duration_u32,
            CtrlIntfModuleMessage*, uint8_t)> try_put_for_cb,
        osPriority priority, uint32_t stack_size, unsigned char *stack_mem,
        const char *name,
        const char *web_page = nullptr);

    virtual ~HTTPCtrlIntfModule();

  private:
    EthernetInterface *_p_net;
    const uint16_t _port;
    const int _timeout;
    const char *_web_page;
    char _http_buff[HTTP_BUFFER_SIZE];

    bool _read_http_request(TCPSocket *client, char *buff, size_t buff_len);
    HttpRequestType _parse_http_request(const char *http_request,
        char *cmd_buff, size_t cmd_buff_len);
    bool _send_all(TCPSocket *client, const char *data, size_t len);
    bool _send_http_response(TCPSocket *client, int status_code,
        const char *reason_phrase, const char *content_type, const char *body);
    void _task() override;
};

#endif /* HTTPCTRLINTFMODULE_HPP_ */
