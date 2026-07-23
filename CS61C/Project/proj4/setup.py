from setuptools import setup, Extension

def main():
    CFLAGS = ['-g', '-Wall', '-std=c99', '-fopenmp', '-mavx', '-mfma', '-pthread', '-O3']
    LDFLAGS = ['-fopenmp']
    mod = Extension('numc',
                    sources=['numc.c', 'matrix.c'],
                    extra_compile_args=CFLAGS,
                    extra_link_args=LDFLAGS)
    setup(name='numc',
          version='1.0',
          description='CS61C Project 4: Matrix Library',
          ext_modules=[mod])

if __name__ == "__main__":
    main()
