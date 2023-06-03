#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Car {
    char manufacturer[50];
    int year;
    char plate[10];
    char color[20];
    char entry_date[20];
    float value;
    char observations[100];
};

struct Client {
    char name[50];
    char address[100];
    char cpf[12];
};

struct Seller {
    char name[50];
    char birth_date[20];
    char cpf[12];
    float salary;
    float sales_percentage;
};

void insertCar(FILE *car_file) {
    struct Car car;

    printf("\nInserindo novo carro:\n");
    printf("Fabricante: ");
    scanf(" %[^\n]", car.manufacturer);
    printf("Ano: ");
    scanf("%d", &car.year);
    printf("Placa: ");
    scanf(" %[^\n]", car.plate);
    printf("Cor: ");
    scanf(" %[^\n]", car.color);
    printf("Data de entrada: ");
    scanf(" %[^\n]", car.entry_date);
    printf("Valor: ");
    scanf("%f", &car.value);
    printf("Observacoes: ");
    scanf(" %[^\n]", car.observations);

    fseek(car_file, 0, SEEK_END);
    fwrite(&car, sizeof(struct Car), 1, car_file);

    printf("\nCarro inserido com sucesso!\n");
}

void insertClient(FILE *client_file) {
    struct Client client;

    printf("\nInserindo novo cliente:\n");
    printf("Nome: ");
    scanf(" %[^\n]", client.name);
    printf("Endereco: ");
    scanf(" %[^\n]", client.address);
    printf("CPF: ");
    scanf(" %[^\n]", client.cpf);

    fseek(client_file, 0, SEEK_END);
    fwrite(&client, sizeof(struct Client), 1, client_file);

    printf("\nCliente inserido com sucesso!\n");
}

void insertSeller(FILE *seller_file) {
    struct Seller seller;

    printf("\nInserindo novo vendedor:\n");
    printf("Nome: ");
    scanf(" %[^\n]", seller.name);
    printf("Data de nascimento: ");
    scanf(" %[^\n]", seller.birth_date);
    printf("CPF: ");
    scanf(" %[^\n]", seller.cpf);
    printf("Salario: ");
    scanf("%f", &seller.salary);
    printf("Porcentagem de vendas: ");
    scanf("%f", &seller.sales_percentage);

    fseek(seller_file, 0, SEEK_END);
    fwrite(&seller, sizeof(struct Seller), 1, seller_file);

    printf("\nVendedor inserido com sucesso!\n");
}

void searchCarByYear(FILE *car_file) {
    int year;
    printf("\nDigite o ano de fabricacao: ");
    scanf("%d", &year);

    struct Car car;
    fseek(car_file, 0, SEEK_SET);
    int found = 0;

    while (fread(&car, sizeof(struct Car), 1, car_file)) {
        if (car.year == year) {
            printf("\nFabricante: %s\n", car.manufacturer);
            printf("Placa: %s\n", car.plate);
            printf("Cor: %s\n", car.color);
            printf("Data de entrada: %s\n", car.entry_date);
            printf("Valor: %.2f\n", car.value);
            printf("Observacoes: %s\n", car.observations);
            found = 1;
        }
    }

    if (!found) {
        printf("\nNenhum carro encontrado para o ano de fabricacao %d\n", year);
    }
}

void searchCarByModel(FILE *car_file) {
    char model[50];
    printf("\nDigite o modelo: ");
    scanf(" %[^\n]", model);

    struct Car car;
    fseek(car_file, 0, SEEK_SET);
    int found = 0;

    while (fread(&car, sizeof(struct Car), 1, car_file)) {
        if (strstr(car.manufacturer, model) != NULL) {
            printf("\nFabricante: %s\n", car.manufacturer);
            printf("Placa: %s\n", car.plate);
            printf("Cor: %s\n", car.color);
            printf("Data de entrada: %s\n", car.entry_date);
            printf("Valor: %.2f\n", car.value);
            printf("Observacoes: %s\n", car.observations);
            found = 1;
        }
    }

    if (!found) {
        printf("\nNenhum carro encontrado para o modelo %s\n", model);
    }
}

void searchCarByPlate(FILE *car_file) {
    char plate[10];
    printf("\nDigite a placa: ");
    scanf(" %[^\n]", plate);

    struct Car car;
    fseek(car_file, 0, SEEK_SET);
    int found = 0;

    while (fread(&car, sizeof(struct Car), 1, car_file)) {
        if (strcmp(car.plate, plate) == 0) {
            printf("\nFabricante: %s\n", car.manufacturer);
            printf("Placa: %s\n", car.plate);
            printf("Cor: %s\n", car.color);
            printf("Data de entrada: %s\n", car.entry_date);
            printf("Valor: %.2f\n", car.value);
            printf("Observacoes: %s\n", car.observations);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("\nNenhum carro encontrado para a placa %s\n", plate);
    }
}

void updateCarData(FILE *car_file) {
    char plate[10];
    printf("\nDigite a placa do carro que deseja alterar os dados: ");
    scanf(" %[^\n]", plate);

    struct Car car;
    fseek(car_file, 0, SEEK_SET);
    int found = 0;

    while (fread(&car, sizeof(struct Car), 1, car_file)) {
        if (strcmp(car.plate, plate) == 0) {
            printf("\nFabricante: %s\n", car.manufacturer);
            printf("Placa: %s\n", car.plate);
            printf("Cor: %s\n", car.color);
            printf("Data de entrada: %s\n", car.entry_date);
            printf("Valor: %.2f\n", car.value);
            printf("Observacoes: %s\n", car.observations);

            printf("\nDigite os novos dados:\n");
            printf("Fabricante: ");
            scanf(" %[^\n]", car.manufacturer);
            printf("Ano: ");
            scanf("%d", &car.year);
            printf("Cor: ");
            scanf(" %[^\n]", car.color);
            printf("Data de entrada: ");
            scanf(" %[^\n]", car.entry_date);
            printf("Valor: ");
            scanf("%f", &car.value);
            printf("Observacoes: ");
            scanf(" %[^\n]", car.observations);

            fseek(car_file, -((long)sizeof(struct Car)), SEEK_CUR);
            fwrite(&car, sizeof(struct Car), 1, car_file);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("\nNenhum carro encontrado para a placa %s\n", plate);
    }
}

void deleteCar(FILE *car_file) {
    char plate[10];
    printf("\nDigite a placa do carro que deseja excluir: ");
    scanf(" %[^\n]", plate);

    struct Car car;
    FILE *temp_file = fopen("temp.dat", "wb");

    fseek(car_file, 0, SEEK_SET);
    int found = 0;

    while (fread(&car, sizeof(struct Car), 1, car_file)) {
        if (strcmp(car.plate, plate) != 0) {
            fwrite(&car, sizeof(struct Car), 1, temp_file);
        } else {
            found = 1;
        }
    }

    fclose(car_file);
    fclose(temp_file);

    if (found) {
        remove("carros.dat");
        rename("temp.dat", "carros.dat");
        printf("\nCarro excluido com sucesso!\n");
    } else {
        remove("temp.dat");
        printf("\nNenhum carro encontrado para a placa %s\n", plate);
    }
}

void deleteClient(FILE *client_file) {
    char cpf[12];
    printf("\nDigite o CPF do cliente que deseja excluir: ");
    scanf(" %[^\n]", cpf);

    struct Client client;
    FILE *temp_file = fopen("temp.dat", "wb");

    fseek(client_file, 0, SEEK_SET);
    int found = 0;

    while (fread(&client, sizeof(struct Client), 1, client_file)) {
        if (strcmp(client.cpf, cpf) != 0) {
            fwrite(&client, sizeof(struct Client), 1, temp_file);
        } else {
            found = 1;
        }
    }

    fclose(client_file);
    fclose(temp_file);

    if (found) {
        remove("clientes.dat");
        rename("temp.dat", "clientes.dat");
        printf("\nCliente excluido com sucesso!\n");
    } else {
        remove("temp.dat");
        printf("\nNenhum cliente encontrado para o CPF %s\n", cpf);
    }
}

void deleteSeller(FILE *seller_file) {
    char cpf[12];
    printf("\nDigite o CPF do vendedor que deseja excluir: ");
    scanf(" %[^\n]", cpf);

    struct Seller seller;
    FILE *temp_file = fopen("temp.dat", "wb");

    fseek(seller_file, 0, SEEK_SET);
    int found = 0;

    while (fread(&seller, sizeof(struct Seller), 1, seller_file)) {
        if (strcmp(seller.cpf, cpf) != 0) {
            fwrite(&seller, sizeof(struct Seller), 1, temp_file);
        } else {
            found = 1;
        }
    }

    fclose(seller_file);
    fclose(temp_file);

    if (found) {
        remove("vendedores.dat");
        rename("temp.dat", "vendedores.dat");
        printf("\nVendedor excluido com sucesso!\n");
    } else {
        remove("temp.dat");
        printf("\nNenhum vendedor encontrado para o CPF %s\n", cpf);
    }
}

void listCars(FILE *car_file) {
    struct Car car;
    fseek(car_file, 0, SEEK_SET);

    printf("\nListando carros:\n");

    while (fread(&car, sizeof(struct Car), 1, car_file)) {
        printf("\nFabricante: %s\n", car.manufacturer);
        printf("Ano: %d\n", car.year);
        printf("Placa: %s\n", car.plate);
        printf("Cor: %s\n", car.color);
        printf("Data de entrada: %s\n", car.entry_date);
        printf("Valor: %.2f\n", car.value);
        printf("Observacoes: %s\n", car.observations);
    }
}

void listSellers(FILE *seller_file) {
    struct Seller seller;
    fseek(seller_file, 0, SEEK_SET);

    printf("\nListando vendedores:\n");

    while (fread(&seller, sizeof(struct Seller), 1, seller_file)) {
        printf("\nNome: %s\n", seller.name);
        printf("Data de nascimento: %s\n", seller.birth_date);
        printf("CPF: %s\n", seller.cpf);
        printf("Salario: %.2f\n", seller.salary);
        printf("Porcentagem de vendas: %.2f\n", seller.sales_percentage);
    }
}

void listClients(FILE *client_file) {
    struct Client client;
    fseek(client_file, 0, SEEK_SET);

    printf("\nListando clientes:\n");

    while (fread(&client, sizeof(struct Client), 1, client_file)) {
        printf("\nNome: %s\n", client.name);
        printf("Endereco: %s\n", client.address);
        printf("CPF: %s\n", client.cpf);
    }
}

void listCarsByPriceRange(FILE *car_file) {
    float min_value, max_value;
    printf("\nDigite o valor minimo: ");
    scanf("%f", &min_value);
    printf("Digite o valor maximo: ");
    scanf("%f", &max_value);

    struct Car car;
    fseek(car_file, 0, SEEK_SET);
    int found = 0;

    while (fread(&car, sizeof(struct Car), 1, car_file)) {
        if (car.value >= min_value && car.value <= max_value) {
            printf("\nFabricante: %s\n", car.manufacturer);
            printf("Placa: %s\n", car.plate);
            printf("Cor: %s\n", car.color);
            printf("Data de entrada: %s\n", car.entry_date);
            printf("Valor: %.2f\n", car.value);
            printf("Observacoes: %s\n", car.observations);
            found = 1;
        }
    }

    if (!found) {
        printf("\nNenhum carro encontrado dentro do intervalo de valores %.2f e %.2f\n", min_value, max_value);
    }
}

int main() {
    printf("\033[1m"); // Ativa o negrito
    printf("\033[31m"); // Define a cor vermelha
    FILE *car_file = fopen("carros.dat", "ab+");
    FILE *client_file = fopen("clientes.dat", "ab+");
    FILE *seller_file = fopen("vendedores.dat", "ab+");
    int option;

    do {
        printf("\n--- Concessionaria ---\n");
        printf("1 - Inserir Carro\n");
        printf("2 - Inserir Cliente\n");
        printf("3 - Inserir Vendedor\n");
        printf("4 - Consultar Carros por Ano\n");
        printf("5 - Consultar Carros por Modelo\n");
        printf("6 - Consultar Carros por Placa\n");
        printf("7 - Alterar Dados do Carro\n");
        printf("8 - Excluir Carro\n");
        printf("9 - Excluir Cliente\n");
        printf("10 - Excluir Vendedor\n");
        printf("11 - Listar Carros\n");
        printf("12 - Listar Vendedores\n");
        printf("13 - Listar Clientes\n");
        printf("14 - Listar Carros por Faixa de Valor\n");
        printf("15 - Finalizar Programa\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &option);

        switch (option) {
            case 1:
                insertCar(car_file);
                break;
            case 2:
                insertClient(client_file);
                break;
            case 3:
                insertSeller(seller_file);
                break;
            case 4:
                searchCarByYear(car_file);
                break;
            case 5:
                searchCarByModel(car_file);
                break;
            case 6:
                searchCarByPlate(car_file);
                break;
            case 7:
                updateCarData(car_file);
                break;
            case 8:
                deleteCar(car_file);
                break;
            case 9:
                deleteClient(client_file);
                break;
            case 10:
                deleteSeller(seller_file);
                break;
            case 11:
                listCars(car_file);
                break;
            case 12:
                listSellers(seller_file);
                break;
            case 13:
                listClients(client_file);
                break;
            case 14:
                listCarsByPriceRange(car_file);
                break;
            case 15:
                printf("\nPrograma finalizado.\n");
                break;
            default:
                printf("\nOpcao invalida!\n");
                break;
        }
    } while (option != 15);

    fclose(car_file);
    fclose(client_file);
    fclose(seller_file);

    return 0;
}
