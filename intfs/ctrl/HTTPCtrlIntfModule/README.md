# HTTPCtrlIntfModule

## Overview

`HTTPCtrlIntfModule` provides an HTTP interface for the command protocol handled by `CtrlCoreModule`.
It allows a web page or any HTTP client to send device commands and receive responses.

* receive command
* forward to `CtrlCoreModule`
* wait for execution
* return the response

It does **not implement application logic**. It only acts as a transport layer between HTTP and the control core.

---

# Responsibilities

The module performs three main tasks:

1. Host a static web page.
2. Receive commands through HTTP.
3. Forward commands to the control core and return the response.

All command parsing and execution remain inside `CtrlCoreModule`.

---

# HTTP Endpoints

## `GET /`

Returns the static web page provided when the module is instantiated.

Example:

```text
GET /
```

Response:

```text
HTTP/1.1 200 OK
Content-Type: text/html
```

---

## `POST /cmd`

Used to send commands to the device.

Example request:

```text
POST /cmd
Content-Type: text/plain

@CHA 1 ?
```

Example response:

```text
HTTP/1.1 200 OK
Content-Type: text/plain

OK>CHA 1: V=12.5 I=0.8
```

The response body is exactly the output produced by the command handler.

---

# Command Flow

```text
Browser
   ↓
POST /cmd
   ↓
HTTPCtrlIntfModule
   ↓
CtrlIntfModuleMessage
   ↓
CtrlCoreModule
   ↓
Command response
   ↓
HTTP response
```

---

# Web Page Requirements

A web page using this interface must:

1. Send commands using `POST /cmd`
2. Place the command in the HTTP body
3. Expect a **plain text response**

Example JavaScript:

```javascript
fetch("/cmd", {
  method: "POST",
  headers: { "Content-Type": "text/plain" },
  body: "@CHA 1 ?"
})
.then(r => r.text())
.then(data => console.log(data));
```

The page is responsible for:

* parsing responses
* updating the UI
* managing polling if needed

---

