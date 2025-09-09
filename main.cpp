#include "MsgpackWrapper.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

typedef enum { uAdmin = 42, uViewer } TUserRole;

class UserDto : public MsgpackObject {
  public:
    MsgpackValue<char *> Name;
    MsgpackValue<uint32_t> Role;

    UserDto(const char *name = {}, const TUserRole role = {})
        : Name(this, 0, name), //
          Role(this, 1, role) {};
};

int main(void) {
    char buffer[2048];

    UserDto outUserDto("DemoWrapper", uAdmin);
    auto writed = outUserDto.Write(buffer, sizeof(buffer));
    fprintf(stdout,
            "out UserDto(%s, %u) serialized to %lu bytes\n",
            outUserDto.Name.Get(),
            outUserDto.Role.Get(),
            writed);

    UserDto inUserDto;
    auto res = inUserDto.TryParse(buffer, writed);
    if (res) {
        fprintf(stdout,
                "in UserDto(%s, %u) deserialized successfully\n",
                outUserDto.Name.Get(),
                outUserDto.Role.Get());
    } else {
        fprintf(stderr,
                "in UserDto(%s, %u) deserialized with error\n",
                outUserDto.Name.Get(),
                outUserDto.Role.Get());
    }

    return 0;
}
