from conans import ConanFile, CMake

class libGPCFontsConan(ConanFile):
  name = "libGPCFonts"
  version = "0.1.1"
  url = "https://github.com/JPGygax68/libGPCFonts.git"
  #settings = "os", "compiler", "build_type", "arch"
  #generators = "cmake"
  exports = "include/*"

  #def build(self):
  #  cmake = CMake(self.settings)
  #  self.run('cmake %s %s' % (self.conanfile_directory, cmake.command_line))
  #  self.run("cmake --build . %s" % cmake.build_config)

  def package(self):
    self.copy("include/*", dst=".") # TODO: better way ?

  #def package_info(self):
