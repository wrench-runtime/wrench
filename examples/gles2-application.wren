// import "buffer" for Buffer

// var b = Buffer.new(32)

// b.writeUint16(0, 1)
// b.writeUint16(16, 2)
// System.print(b.readUint16(0))
// System.print(b.readUint16(16))

// var SDL_OPENGL = 0x00000002
// System.print(SDL_OPENGL)

import "wren_gles2_app" for Gles2Application
import "wren_sdl2" for SdlEventType
import "wren_gles2" for GL, ClearFlag

var app = Gles2Application.new()
app.createWindow(320,240,"Hello World")

var quit = false

while(!quit){
  var ev = null
  while(ev = app.poll()){
    if(ev.type == SdlEventType.Quit) quit = true
  }
  GL.clearColor(1,0,0,1)
  GL.clear(ClearFlag.COLOR_BUFFER_BIT)
  app.swap()
  app.checkErrors()
}