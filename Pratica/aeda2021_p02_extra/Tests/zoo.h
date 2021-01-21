#ifndef ZOO_H_
#define ZOO_H_

#include "animal.h"
#include <vector>

class Zoo {
	vector<Animal *> animals;
	vector<Veterinary *> veterinarians;
public:
    /**
     *
     * @return Number of elements of vector animals
     */
	unsigned numAnimals() const;
	/**
	 *
	 * @return Number of elements of vector veterinarians
	 */
	unsigned numVeterinarians() const;
	/**
	 *
	 * @param a1 Endereço do animal a adicionar no vetor animals
	 */
    void addAnimal(Animal *a1);
    /**
     *
     * @return String com as informações separadas por vírgulas
     */
    string getInfo() const;
    /**
     * Verifica se um determinado animal é jovem
     * @param nameA Nome do animal a analisar
     * @return true if the animal is young, false otherwise
     */
    bool isYoung(string nameA);
    /**
     *
     * @param isV Ficheiro .txt com o nome dos veterinarios seguidos do codigo
     */
    void allocateVeterinarians(istream &isV);
    /**
     * Os animais ao qual este veterinario estava atribuido, passam a ter o vet seguinte no vetor
     * @param nameV Nome do veterinario a remover do vetor veterinarians
     * @return True se existir um vet c esse nome
     */
    bool removeVeterinary(string nameV);
    /**
     *
     * @param zoo2 Outro zoo para comparar
     * @return True se a somadas idades do primeiro for menor
     */
    bool operator < (Zoo& zoo2) const;
};


#endif /* ZOO_H_ */
