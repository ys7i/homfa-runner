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
    if (os.path.exists("tfhe")):
      return
    self.run("git clone https://github.com/tfhe/tfhe.git && cd tfhe && git checkout d7ec12f3be4528968a51d348f438dc2165e0fa0a")