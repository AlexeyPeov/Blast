# Blast
Building a multiplayer game

How to run:

    LINUX
        git checkout linux (linux branch)
        
        if you use CLion, copy these directories to cmake-build-debug or cmake-build-release
            - textures
            - sounds
            - src/shaders
            - server_config.txt
            
        
        
        if you dont, just run these commands:
        
        cmake .
        make
        ./BLAST

    
    Windows
        there is a 'windows release' dir, the BLAST.exe is in there. Just run it
        Dont forget to modify the server_config.txt, otherwise the game will crash..
