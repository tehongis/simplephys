from distutils.core import setup, Extension
# python3 .\setup.py build


def main():
    setup(name="simplephys",
          version="1.0.0",
          description="Collection of fast gamemath functions.",
          url="https://nourl.net/",
          author="Tero hongisto",
          author_email="tehongis@gmail.com",
          ext_modules=[Extension("simplephys", ["main.c"])])

if __name__ == "__main__":
    main()