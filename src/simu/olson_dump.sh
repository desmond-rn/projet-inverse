#!/bin/bash

# Script pour generer les donnees en variant 'rho', 'sigma_a', et 'sigma_c'
#   Ces variables ainsi sont ecrites dans 'cfg_part_1.txt'
#   Les constantes pour cette simulation sont ecrites dans 'cfg_part_2.txt'
#   Les fichiers 'cfg_part_1.txt' et 'cfg_part_2.txt' forment le fichier de configuaration dans 'src/config/dump.cfg'

# fichiers d'exportation
file_1=data/df_temporal_olson.csv
file_2=data/df_spatial_olson.csv

# Pour vider les fichiers d'exportation. Et remplacer le contenu par les en-tetes du csv
overwrite=false
if [ "$overwrite" = true ] ; then
    cat src/simu/headers_temporal.txt > "$file_1"
    cat src/simu/headers_spatial.txt > "$file_2"
fi

# Pour generer 'rho' entre rho_min et rho_max
rho_min=0.38214
rho_max=0.38214
nbiter_rho=1
i=0
a1=$(awk -v i="${i}" -v nbiter="${nbiter_rho}" -v min="${rho_min}" -v max="${rho_max}" 'BEGIN{print ((max-min)/(nbiter-i))}')
b1=$(awk -v min="${rho_min}" 'BEGIN{print (min)}')

# Pour generer 'sigma_a' entre sigma_a_min et sigma_a_max
sigma_a_min=0
sigma_a_max=0
nbiter_sigma_a=1
j=0
a2=$(awk -v j="${j}" -v nbiter="${nbiter_sigma_a}" -v min="${sigma_a_min}" -v max="${sigma_a_max}" 'BEGIN{print ((max-min)/(nbiter-j))}')
b2=$(awk -v min="${sigma_a_min}" 'BEGIN{print (min)}')

# Pour generer 'sigma_c' entre sigma_c_min et sigma_c_max
sigma_c_min=0
sigma_c_max=0
nbiter_sigma_c=1
k=0
# a3=$(awk -v k="${k}" -v nbiter="${nbiter_sigma_c}" -v min="${sigma_c_min}" -v max="${sigma_c_max}" 'BEGIN{print ((max-min)/(nbiter-k))}')
a3=10
b3=$(awk -v min="${sigma_c_min}" 'BEGIN{print (min)}')

rho=0
sigma_a=0
sigma_c=0
c=0
for (( i = 1 ; i <= $nbiter_rho; i++ )); do
    # rho=$(awk -v i="${i}" -v a="${a1}" -v b="${b1}" 'BEGIN{print (a*i+b)}')
    rho="0.056234"
    for (( j = 1 ; j <= $nbiter_sigma_a; j++ )); do
        # sigma_a=$(awk -v j="${j}" -v a="${a2}" -v b="${b2}" 'BEGIN{print (a*j+b)}')
        sigma_a="0.01003/(T^3)"
        # sigma_a="1"
        for (( k = 1 ; k <= $nbiter_sigma_c; k++ )); do
            # sigma_c=$(awk -v k="${k}" -v a="${a3}" -v b="${b3}" 'BEGIN{print (a^k+b)}')
            sigma_c="0"
            echo -e "sigma_c $sigma_c\nrho $rho\nsigma_a $sigma_a\n\nexport_temporal $file_1\nexport_spatial $file_2\n" > src/simu/olson_part_1.txt
            cat src/simu/olson_part_1.txt src/simu/olson_part_2.txt > src/config/dump.cfg
            build/transfer src/config/dump.cfg > /dev/null
        done
    done
done

