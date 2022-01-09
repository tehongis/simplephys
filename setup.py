from distutils.core import setup, Extension

def main():
    setup(name="pysimplephys",
          version="1.0.0",
          description="Collection of fast gamemath functions.",
          author="Tero hongisto",
          author_email="tehongis@gmail.com",
          ext_modules=[Extension("pysimplephys", ["main.c"])])

if __name__ == "__main__":
    main()