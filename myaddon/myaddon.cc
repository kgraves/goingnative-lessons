#include <nan.h>
#include <iostream>

// check if on linux
#ifndef _WIN32
#include <unistd.h>
#endif

using namespace v8;

NAN_METHOD(Delay) {
  int num = info[0]->IntegerValue();

  // windows vs POSIX-compliant check
  #ifdef _WIN32
  Sleep(num);
  #else
  usleep(num * 1000);
  #endif

  v8::Local<Function> callback = info[1].As<Function>();
  Nan::MakeCallback(Nan::GetCurrentContext()->Global(), callback, 0, NULL);
}

NAN_MODULE_INIT(Init) {
  Nan::Set(target, Nan::New("delay").ToLocalChecked(),
      Nan::GetFunction(Nan::New<FunctionTemplate>(Delay)).ToLocalChecked());
}

NODE_MODULE(myaddon, Init)
