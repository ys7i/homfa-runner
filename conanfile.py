from conans import ConanFile, CMake
import os

class HomfaRunnerConan(ConanFile):
  settings="os", "compiler", "build_type", "arch"
  requires = "cli11/2.3.1", "spdlog/1.11.0", "fmt/9.1.0", "gtest/1.12.1"
  generators = "cmake"

  def imports(self):
    self.copy("*.dll", dst="bin", src="bin") # From bin to bin
    self.copy("*.dylib*", dst="bin", src="lib") # From lib to bin
    self.source()

  def build(self):
    cmake = CMake(self)
    cmake.configure()
    self.run('cmake --build ..')


  def source(self):
    if (os.path.exists("TFHEpp")):
      return
    self.run("git clone https://github.com/virtualsecureplatform/TFHEpp.git --recursive && cd TFHEpp && git checkout 36020be")