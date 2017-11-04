#include "cliente.h"

void insereCliente(_CLIENTE* cliente)
{
  cliente->status = 1;
  nome(cliente);
  cpf(cliente->cpf);
  estado(cliente);
  salario(cliente);
}

void nome(_CLIENTE* cliente)
{
  int x = rand() % 50;
  char nomes[][TAM] = {"Alberto Carrilho", "Alice Sousa do Prado", "Alípio Aires", "Antero Rebello", "Antónia Vaz",
                         "Apoena Faustino", "Bernardete Felipe", "Bernardina Tavares", "Bernardo Pena", "Brás Carballo",
                         "Caubi Cordero", "Cesário Ribas", "Clotilde Seixas", "Diamantino Caneira", "Emanuel Salazar", "Felícia Vaz",
                         "Frederico Cartaxo", "Gui Cotegipe", "Honório Regueira", "Horácio Infante", "Ismael Pinto", "Iva Buenaventura",
                         "Jaime Valladares", "Jorgina Gorjão", "Jorgina Quintana", "Josué Baptista", "Júlia Araújo", "Júlia Noite",
                         "Mateus Felgueiras", "Moacir Ribeiro", "Nivaldo Taveira", "Odete Faro", "Odete Fiães", "Ovídio França", "Paulina Bonilha",
                         "Pedro Pajares", "Quintiliana Barateiro", "Rafael Álvarez", "Rafaela Vidal", "Raul Júdice", "Renata Lustosa", "Telo Sardina",
                         "Tomás Bernardes", "Tomásia Rego", "Umbelina Melgaço", "Veridiano Belmonte", "Verónica Suaçuna", "Virgília Carvalhal", "Xisto Cysneiros",
                          "Zuriel Varella"};
    strcpy(cliente->nome, nomes[x]);
}
void cpf(char* cpf)
{
  char cpfTemp[12];
  gerarCpf(cpfTemp);
  insere_pontuacao_cpf(cpfTemp, cpf);
}

void estado(_CLIENTE* cliente)
{
  char est[][5] = {"MS","SP","RJ","MT","PR"};
  int x = rand() % 5;
    strcpy(cliente->endereco.estado, est[x]);
    cidade(cliente, x);
    telResidencial(cliente, x);
    telCelular(cliente, x);
}
void cidade(_CLIENTE* cliente, int x)
{
  char cidades_MS[][TAM] = {"Campo Grande","Dourados","Fatima do Sul","Bonito","Tres Lagoas"};
  char cidades_SP[][TAM] = {"Sao Paulo","Braganca Paulista","Votuporanga","Campinas","Santa Barbara D'Oeste"};
  char cidades_RJ[][TAM] = {"Volta Redonda","Araruama","Rio das Ostras","Queimados","Seropedica"};
  char cidades_MT[][TAM] = {"Cuiaba","Juina","Porto dos Gauchos ","Sorriso","Vila Atlântica"};
  char cidades_PR[][TAM] = {"Foz do Iguacu","Francisco Beltrao","Telemarco Borda","Toledo","Umuarama"};

  int y = rand() % 5;
  switch (x) {
    case 0:
          strcpy(cliente->endereco.cidade, cidades_MS[y]);
          bairro_MS(cliente, y);
          break;
    case 1:
          strcpy(cliente->endereco.cidade, cidades_SP[y]);
          bairro_SP(cliente, y);
          break;
    case 2:
          strcpy(cliente->endereco.cidade, cidades_RJ[y]);
          bairro_RJ(cliente, y);
          break;
    case 3:
          strcpy(cliente->endereco.cidade, cidades_MT[y]);
          bairro_MT(cliente, y);
          break;
    case 4:
          strcpy(cliente->endereco.cidade, cidades_PR[y]);
          bairro_PR(cliente, y);
          break;
  }

}

/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-PARANA=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
void bairro_PR(_CLIENTE* cliente, int x)
{
  char bairros_Cidade_1[][TAM] = {"Loteamento Mata Verde", "Parque Presidente II", "Jardim Eliza II", "Jardim Amazonas", "Jardim São Paulo I"};
  char bairros_Cidade_2[][TAM] = {"São Miguel", "Luther King", "Pinheirinho", "Aeroporto", "Pinheirinho"};
  char bairros_Cidade_3[][TAM] = {"Nossa Senhora do Perpétuo Socorro", "Ana Mary", "Vila Esperança", "Vila São Francisco de Assis", "Parque Limeira Área VI"};
  char bairros_Cidade_4[][TAM] = {"Vila Industrial", "Centro", "Jardim Porto Alegre", "São Francisco", "Jardim Santa Maria"};
  char bairros_Cidade_5[][TAM] = {"Jardim Maria Lúcia", "Conjunto Habitacional Sonho Meu", "Parque Industrial Comercial Novo Horizonte", "Parque San Caetano", "Zona V"};
  int y = rand() % 5;
  switch (x) {
    case 0:
          strcpy(cliente->endereco.bairro, bairros_Cidade_1[y]);
          break;
    case 1:
          strcpy(cliente->endereco.bairro, bairros_Cidade_2[y]);
          break;
    case 2:
          strcpy(cliente->endereco.bairro, bairros_Cidade_3[y]);
          break;
    case 3:
          strcpy(cliente->endereco.bairro, bairros_Cidade_4[y]);
          break;
    case 4:
          strcpy(cliente->endereco.bairro, bairros_Cidade_5[y]);
          break;
  }
  rua_PR(cliente, x, y);
}
void rua_PR(_CLIENTE* cliente, int x,int y)
{
  char rua_Cidade_1[][TAM] = {"Rua São Vicente", "Travessa Joana Moleda", "Rua Ernesto Keller", "Avenida República Argentina", "Rua do Semeador"};
  char rua_Cidade_2[][TAM] = {"Rua Rio Negro", "Rua João-de-barro", "Rua dos Pinhais", "Travessa Antonio Coterno", "Rua José Casagrande"};
  char rua_Cidade_3[][TAM] = {"Travessa Mônaco", "Estrada dos Guararapes", "Rua Salgueiro", "Rua da Cruz", "Travessa Baraúna"};
  char rua_Cidade_4[][TAM] = {"Rua Primeiro de Julho", "Rua Barão do Rio Branco", "Rua Alberto Dalcanale", "Rua Avelino Niedermeier", "Rua Matelândia"};
  char rua_Cidade_5[][TAM] = {"Rua Sete", "Rua Casimiro de Abreu", "Rua Dois", "Rua Benjamin Constant", "Avenida Rio Grande do Norte"};

  switch (x) {
    case 0:
          strcpy(cliente->endereco.rua, rua_Cidade_1[y]);
          break;
    case 1:
          strcpy(cliente->endereco.rua, rua_Cidade_2[y]);
          break;
    case 2:
          strcpy(cliente->endereco.rua, rua_Cidade_3[y]);
          break;
    case 3:
          strcpy(cliente->endereco.rua, rua_Cidade_4[y]);
          break;
    case 4:
          strcpy(cliente->endereco.rua, rua_Cidade_5[y]);
          break;
  }
  cep_PR(cliente, x, y);
}
void cep_PR(_CLIENTE* cliente, int x, int y)
{
  char cep_Cidade_1[][TAM] = {"85.853-680", "85.863-650", "85.854-200", "85.857-188", "85.856-375"};
  char cep_Cidade_2[][TAM] = {"85.602-180", "85.605-630", "85.606-190", "85.603-890", "85.606-240"};
  char cep_Cidade_3[][TAM] = {"84.265-140", "84.263-090", "84.272-240", "84.264-490", "84.271-440"};
  char cep_Cidade_4[][TAM] = {"85.904-200", "85.901-180", "85.906-402", "85.915-227", "85.903-070"};
  char cep_Cidade_5[][TAM] = {"87.501-660", "87.510-007", "87.507-060", "87.506-255", "87.504-000"};

  switch (x) {
    case 0:
          strcpy(cliente->endereco.cep, cep_Cidade_1[y]);
          break;
    case 1:
          strcpy(cliente->endereco.cep, cep_Cidade_2[y]);
          break;
    case 2:
          strcpy(cliente->endereco.cep, cep_Cidade_3[y]);
          break;
    case 3:
          strcpy(cliente->endereco.cep, cep_Cidade_4[y]);
          break;
    case 4:
          strcpy(cliente->endereco.cep, cep_Cidade_5[y]);
          break;
  }
  numero(cliente);
}
/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-MATO GROSSO-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
void bairro_MT(_CLIENTE* cliente, int x)
{
  char bairros_Cidade_1[][TAM] = {"Jardim Renascer", "Jardim das Palmeiras", "Parque Georgia", "Morada dos Nobres", "Jardim Universitário"};
  char bairros_Cidade_2[][TAM] = {"Centro", "Centro", "Centro", "Padre Duílio", "Padre Duílio"};
  char bairros_Cidade_3[][TAM] = {"Centro", "Centro", "São João", "Centro", "Centro"};
  char bairros_Cidade_4[][TAM] = {"Centro", "Caravaggio", "Caravaggio", "Centro", "Centro"};
  char bairros_Cidade_5[][TAM] = {"Centro", "Centro", "Centro", "Centro", "Centro"};
  int y = rand() % 5;
  switch (x) {
    case 0:
          strcpy(cliente->endereco.bairro, bairros_Cidade_1[y]);
          break;
    case 1:
          strcpy(cliente->endereco.bairro, bairros_Cidade_2[y]);
          break;
    case 2:
          strcpy(cliente->endereco.bairro, bairros_Cidade_3[y]);
          break;
    case 3:
          strcpy(cliente->endereco.bairro, bairros_Cidade_4[y]);
          break;
    case 4:
          strcpy(cliente->endereco.bairro, bairros_Cidade_5[y]);
          break;
  }
  rua_MT(cliente, x, y);
}
void rua_MT(_CLIENTE* cliente, int x,int y)
{
  char rua_Cidade_1[][TAM] = {"Rua Bandeirantes", "Rua Três", "Rua Cariré", "Rua Conde D' Eu", "Rua Projetada 26"};
  char rua_Cidade_2[][TAM] = {"Avenida dos Jambos 1151", "Avenida dos Jambos", "Avenida dos Jambos", "Avenida Joinville", "Avenida Joinville"};
  char rua_Cidade_3[][TAM] = {"Avenida Diamantino 1297", "Avenida Diamantino", "Rua Principal", "Avenida Diamantino 1297", "Avenida Diamantino"};
  char rua_Cidade_4[][TAM] = {"Rua Eurico Gaspar Dutra ", "Rodovia Mt 242", "Rodovia Mt 242", "Avenida Tancredo Neves 543 8º Sala", "Avenida Tancredo Neves 543 8º Sala"};
  char rua_Cidade_5[][TAM] = {"Rua Principal", "Rua Principal", "Rua Principal", "Rua Principal", "Rua Principal"};

  switch (x) {
    case 0:
          strcpy(cliente->endereco.rua, rua_Cidade_1[y]);
          break;
    case 1:
          strcpy(cliente->endereco.rua, rua_Cidade_2[y]);
          break;
    case 2:
          strcpy(cliente->endereco.rua, rua_Cidade_3[y]);
          break;
    case 3:
          strcpy(cliente->endereco.rua, rua_Cidade_4[y]);
          break;
    case 4:
          strcpy(cliente->endereco.rua, rua_Cidade_5[y]);
          break;
  }
  cep_MT(cliente, x, y);
}
void cep_MT(_CLIENTE* cliente, int x, int y)
{
  char cep_Cidade_1[][TAM] = {"78.061-376", "78.080-268", "78.085-545", "78.068-020", "78.075-600"};
  char cep_Cidade_2[][TAM] = {"78.320-970", "78.320-970", "78.320-970", "78.320-971", "78.320-971"};
  char cep_Cidade_3[][TAM] = {"78.560-970", "78.560-970", "78.560-971", "78.560-970", "78.560-970"};
  char cep_Cidade_4[][TAM] = {"78.890-970", "78.890-972", "78.890-972", "78.890-971", "78.890-971"};
  char cep_Cidade_5[][TAM] = {"78.536-970", "78.536-970", "78.536-970", "78.536-970", "78.536-970"};

  switch (x) {
    case 0:
          strcpy(cliente->endereco.cep, cep_Cidade_1[y]);
          break;
    case 1:
          strcpy(cliente->endereco.cep, cep_Cidade_2[y]);
          break;
    case 2:
          strcpy(cliente->endereco.cep, cep_Cidade_3[y]);
          break;
    case 3:
          strcpy(cliente->endereco.cep, cep_Cidade_4[y]);
          break;
    case 4:
          strcpy(cliente->endereco.cep, cep_Cidade_5[y]);
          break;
  }
  numero(cliente);
}
/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-RIO DE JANEIRO=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
void bairro_RJ(_CLIENTE* cliente, int x)
{
  char bairros_Cidade_1[][TAM] = {"Colorado", "Vila Americana", "Jardim Normandia", "São Lucas", "Siderlândia"};
  char bairros_Cidade_2[][TAM] = {"Morro Grande", "Centro", "Centro", "Morro Grande", "Praia Seca"};
  char bairros_Cidade_3[][TAM] = {"Viverde I", "Nova Cidade", "Sobradinho Cerveja", "Nova Aliança", "Recanto"};
  char bairros_Cidade_4[][TAM] = {"Roncador", "Vila Scintila", "Vila do Tinguá", "Riachão", "São Manuel"};
  char bairros_Cidade_5[][TAM] = {"Fazenda Caxias", "Ecologia", "UFRRJ", "UFRRJ", "São Miguel"};
  int y = rand() % 5;
  switch (x) {
    case 0:
          strcpy(cliente->endereco.bairro, bairros_Cidade_1[y]);
          break;
    case 1:
          strcpy(cliente->endereco.bairro, bairros_Cidade_2[y]);
          break;
    case 2:
          strcpy(cliente->endereco.bairro, bairros_Cidade_3[y]);
          break;
    case 3:
          strcpy(cliente->endereco.bairro, bairros_Cidade_4[y]);
          break;
    case 4:
          strcpy(cliente->endereco.bairro, bairros_Cidade_5[y]);
          break;
  }
  rua_RJ(cliente, x, y);
}
void rua_RJ(_CLIENTE* cliente, int x,int y)
{
  char rua_Cidade_1[][TAM] = {"Rua Nove", "Servidão Americana", "Rua Henrique Hoppe", "Praça Antônio Frederico Ozanan", "Travessa Benjamim Constant"};
  char rua_Cidade_2[][TAM] = {"Rua João Alberto, s/n", "Avenida Getúlio Vargas 1425 Loja B", "Avenida Getúlio Vargas 1425 Loja B", "Rua João Alberto, s/n", "Estrada de Praia Seca 13195"};
  char rua_Cidade_3[][TAM] = {"Rua Interna Dois", "Rua Jaci Machado", "Rua da Floresta", "Rua Valdecir Barros de Farias", "Rua Jaime Barreiros"};
  char rua_Cidade_4[][TAM] = {"Praça Batalha", "Rua Patrícia", "Rua Itabira", "Rua Frei Caneca", "Rua Etelvina"};
  char rua_Cidade_5[][TAM] = {"Travessa Abgail Vicente de Lima", "Rua Projetada C", "Rua UAV", "Rua UO", "Rua da Lagoa"};

  switch (x) {
    case 0:
          strcpy(cliente->endereco.rua, rua_Cidade_1[y]);
          break;
    case 1:
          strcpy(cliente->endereco.rua, rua_Cidade_2[y]);
          break;
    case 2:
          strcpy(cliente->endereco.rua, rua_Cidade_3[y]);
          break;
    case 3:
          strcpy(cliente->endereco.rua, rua_Cidade_4[y]);
          break;
    case 4:
          strcpy(cliente->endereco.rua, rua_Cidade_5[y]);
          break;
  }
  cep_RJ(cliente, x, y);
}
void cep_RJ(_CLIENTE* cliente, int x, int y)
{
  char cep_Cidade_1[][TAM] = {"27.240-830", "27.212-163", "27.251-290", "27.264-380", "27.273-457"};
  char cep_Cidade_2[][TAM] = {"28.975-970", "28.970-971", "28.970-971", "28.975-970", "28.970-972"};
  char cep_Cidade_3[][TAM] = {"28.894-738", "28.894-486", "28.893-173", "28.893-190", "28.890-636"};
  char cep_Cidade_4[][TAM] = {"26.381-760", "26.320-450", "26.383-160", "26.330-310", "26.317-270"};
  char cep_Cidade_5[][TAM] = {"23.895-190", "23.891-390", "23.897-060", "23.897-035", "23.893-735"};

  switch (x) {
    case 0:
          strcpy(cliente->endereco.cep, cep_Cidade_1[y]);
          break;
    case 1:
          strcpy(cliente->endereco.cep, cep_Cidade_2[y]);
          break;
    case 2:
          strcpy(cliente->endereco.cep, cep_Cidade_3[y]);
          break;
    case 3:
          strcpy(cliente->endereco.cep, cep_Cidade_4[y]);
          break;
    case 4:
          strcpy(cliente->endereco.cep, cep_Cidade_5[y]);
          break;
  }
  numero(cliente);
}
/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-SAO PAULO=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
void bairro_SP(_CLIENTE* cliente, int x)
{
  char bairros_Cidade_1[][TAM] = {"Cambuci", "Jardim Angelina", "Parque Savoy City", "Jardim Promissão", "Chácara Santa Maria"};
  char bairros_Cidade_2[][TAM] = {"Cidade Planejada II", "Jardim Nova Bragança", "Jardim São Miguel", "Jardim do Lago", "Condomínio Jardim das Palmeiras"};
  char bairros_Cidade_3[][TAM] = {"Vila Paes", "Parque Santa Felícia", "Park Residencial Colinas", "Cecap II", "Parque Guarani"};
  char bairros_Cidade_4[][TAM] = {"Vila Andrade Neves", "Residencial São Luís", "Loteamento Residencial Porto Seguro", "Fazenda São Quirino", "Jardim São Gonçalo"};
  char bairros_Cidade_5[][TAM] = {"Vila Grego II", "Jardim Flamboyant", "Jardim Residencial Mariana", "Residencial Furlan", "Residencial São Joaquim"};
  int y = rand() % 5;
  switch (x) {
    case 0:
          strcpy(cliente->endereco.bairro, bairros_Cidade_1[y]);
          break;
    case 1:
          strcpy(cliente->endereco.bairro, bairros_Cidade_2[y]);
          break;
    case 2:
          strcpy(cliente->endereco.bairro, bairros_Cidade_3[y]);
          break;
    case 3:
          strcpy(cliente->endereco.bairro, bairros_Cidade_4[y]);
          break;
    case 4:
          strcpy(cliente->endereco.bairro, bairros_Cidade_5[y]);
          break;
  }
  rua_SP(cliente, x, y);
}
void rua_SP(_CLIENTE* cliente, int x,int y)
{
  char rua_Cidade_1[][TAM] = {"Rua Félix Pola", "Rua Manoel Jácomo", "Rua Plácido Nunes", "Rua Engenheiro Francisco Pitta Brito 138", "Rua Marujal"  };
  char rua_Cidade_2[][TAM] = {"Rua Agostinho Rosa", "Rua João Margarido", "Rua Estevam José do Carmo", "Rua Professor João Ferraz Teixeira", "Avenida dos Eucaliptos"};
  char rua_Cidade_3[][TAM] = {"Rua Presidente Juscelino Kubitschek de Oliveira", "Rua Vereador Luiz Zucolotto", "Avenida Pedro Madrid Sanches", "Rua Pontes Gestal", "Travessa Guarani"};
  char rua_Cidade_4[][TAM] = {"Praça Herberto Seiffert Jacoby", "Edílson Ferreira da Silva", "Bernardo Joaquim da Silva Guimarães", "Engenheiro José Francisco Bento Homem de Mello", "Rua Italia Buratto"};
  char rua_Cidade_5[][TAM] = {"Rua Distrito Federal", "Rua Monte Líbano", "Rua João Cândido Rangel", "Rua Angélica Tremacoldi", "Rua Campinas"};

  switch (x) {
    case 0:
          strcpy(cliente->endereco.rua, rua_Cidade_1[y]);
          break;
    case 1:
          strcpy(cliente->endereco.rua, rua_Cidade_2[y]);
          break;
    case 2:
          strcpy(cliente->endereco.rua, rua_Cidade_3[y]);
          break;
    case 3:
          strcpy(cliente->endereco.rua, rua_Cidade_4[y]);
          break;
    case 4:
          strcpy(cliente->endereco.rua, rua_Cidade_5[y]);
          break;
  }
  cep_SP(cliente, x, y);
}
void cep_SP(_CLIENTE* cliente, int x, int y)
{
  char cep_Cidade_1[][TAM] = {"01.535-030", "04.835-240", "03.570-360", "04.753-900", "05.879-460"};
  char cep_Cidade_2[][TAM] = {"12.922-580", "12.914-350", "12.903-420", "12.914-540", "12.924-310"};
  char cep_Cidade_3[][TAM] = {"15.500-110", "15.505-055", "15.503-395", "15.502-010", "15.501-306"};
  char cep_Cidade_4[][TAM] = {"13.070-291", "13.058-767", "13.057-143", "13.091-700", "13.082-712"};
  char cep_Cidade_5[][TAM] = {"13.451-136", "13.450-640", "13.456-046", "13.451-195", "13.452-040"};

  switch (x) {
    case 0:
          strcpy(cliente->endereco.cep, cep_Cidade_1[y]);
          break;
    case 1:
          strcpy(cliente->endereco.cep, cep_Cidade_2[y]);
          break;
    case 2:
          strcpy(cliente->endereco.cep, cep_Cidade_3[y]);
          break;
    case 3:
          strcpy(cliente->endereco.cep, cep_Cidade_4[y]);
          break;
    case 4:
          strcpy(cliente->endereco.cep, cep_Cidade_5[y]);
          break;
  }
  numero(cliente);
}

/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-MATO GROSSO DO SUL=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
void bairro_MS(_CLIENTE* cliente, int x)
{
  char bairros_Cidade_1[][TAM] = {"Jardim Sao Lourenço", "Jardim Vida Nova", "Residencial Oiti", "Jardim das Virtudes", "Jardim Monte Alegre"};
  char bairros_Cidade_2[][TAM] = {"Izidro Pedroso", "Vila Planalto", "Jardim Agua Boa", "COHAB II", "Vila Planalto"};
  char bairros_Cidade_3[][TAM] = {"Centro", "Centro", "Centro", "Centro", "Centro"};
  char bairros_Cidade_4[][TAM] = {"Centro", "Centro", "Centro", "Centro", "Centro"};
  char bairros_Cidade_5[][TAM] = {"Santos Dumont", "Alto da Boa Vista", "Nossa Senhora Aparecida", "Jardim das Oliveiras", "Vila Piloto"};
  int y = rand() % 5;
  switch (x) {
    case 0:
          strcpy(cliente->endereco.bairro, bairros_Cidade_1[y]);
          break;
    case 1:
          strcpy(cliente->endereco.bairro, bairros_Cidade_2[y]);
          break;
    case 2:
          strcpy(cliente->endereco.bairro, bairros_Cidade_3[y]);
          break;
    case 3:
          strcpy(cliente->endereco.bairro, bairros_Cidade_4[y]);
          break;
    case 4:
          strcpy(cliente->endereco.bairro, bairros_Cidade_5[y]);
          break;
  }
  rua_MS(cliente, x, y);
}
void rua_MS(_CLIENTE* cliente, int x,int y)
{
  char rua_Cidade_1[][TAM] = {"Rua Itápolis", "Rua Gilson N. de Oliveira", "Rua Sir Lancelot", "Rua Nassif El Daher", "Rua Nagem Saad"};
  char rua_Cidade_2[][TAM] = {"Rua Isaac Duarte de Barros", "Rua Monte Alegre", "Rua Ediberto Celestino de Oliveira", "Rua Getúlio Vargas", "Rua João Vicente Ferreira"};
  char rua_Cidade_3[][TAM] = {"Rua Principal, s/n", "Rua Cristobalina Ruiz Cabelo 1186", "Rua Principal", "Rua Cristobalina Ruiz Cabelo 1186", "Rua Principal"};
  char rua_Cidade_4[][TAM] = {"Quadra 14 Quadra 14 Lote", " Pilad Rébua", "Coronel Pilad Rébua", "Rua Coronel Pilad", "Coronel Pilad"};
  char rua_Cidade_5[][TAM] = {"Rua Coronel Lima Figueiredo", "Rua C", "Viela Alexandre Abrão", "Rua Antônio Dias", "Rua José Neme"};

  switch (x) {
    case 0:
          strcpy(cliente->endereco.rua, rua_Cidade_1[y]);
          break;
    case 1:
          strcpy(cliente->endereco.rua, rua_Cidade_2[y]);
          break;
    case 2:
          strcpy(cliente->endereco.rua, rua_Cidade_3[y]);
          break;
    case 3:
          strcpy(cliente->endereco.rua, rua_Cidade_4[y]);
          break;
    case 4:
          strcpy(cliente->endereco.rua, rua_Cidade_5[y]);
          break;
  }
  cep_MS(cliente, x, y);
}


void cep_MS(_CLIENTE* cliente, int x, int y)
{
  char cep_Cidade_1[][TAM] = {"79.041-280", "79.017-786", "79.044-188", "79.115-397", "79.074-046"};
  char cep_Cidade_2[][TAM] = {"79.840-350", "79.826-040", "79.812-230", "79.814-185", "79.826-020"};
  char cep_Cidade_3[][TAM] = {"79.700-971", "79.700-970", "79.700-971", "79.700-970", "79.700-971"};
  char cep_Cidade_4[][TAM] = {"79.290-971", "79.290-970", "79.290-970", "79.290-970", "79.290-970"};
  char cep_Cidade_5[][TAM] = {"79.620-020", "79.640-500", "79.620-166", "79.630-300", "79.612-431"};

  switch (x) {
    case 0:
          strcpy(cliente->endereco.cep, cep_Cidade_1[y]);
          break;
    case 1:
          strcpy(cliente->endereco.cep, cep_Cidade_2[y]);
          break;
    case 2:
          strcpy(cliente->endereco.cep, cep_Cidade_3[y]);
          break;
    case 3:
          strcpy(cliente->endereco.cep, cep_Cidade_4[y]);
          break;
    case 4:
          strcpy(cliente->endereco.cep, cep_Cidade_5[y]);
          break;
  }
  numero(cliente);
}
void numero(_CLIENTE* cliente)
{
  cliente->endereco.numero = 100 + (rand() % 2000);
}

void telResidencial(_CLIENTE* cliente, int Est)
{

  switch (Est) {
    case 0:
            cliente->residencial.telefone[0] = '6';
            cliente->residencial.telefone[1] = '7';
            cliente->residencial.telefone[2] = ' ';
            cliente->residencial.telefone[3] = '3';
            _telResidencial(cliente);
          break;
    case 1:
            cliente->residencial.telefone[0] = '1';
            cliente->residencial.telefone[1] = '1';
            cliente->residencial.telefone[2] = ' ';
            cliente->residencial.telefone[3] = '3';
            _telResidencial(cliente);
          break;
    case 2:
            cliente->residencial.telefone[0] = '2';
            cliente->residencial.telefone[1] = '1';
            cliente->residencial.telefone[2] = ' ';
            cliente->residencial.telefone[3] = '3';
            _telResidencial(cliente);
          break;
    case 3:
            cliente->residencial.telefone[0] = '6';
            cliente->residencial.telefone[1] = '5';
            cliente->residencial.telefone[2] = ' ';
            cliente->residencial.telefone[3] = '3';
            _telResidencial(cliente);
          break;
    case 4:
            cliente->residencial.telefone[0] = '4';
            cliente->residencial.telefone[1] = '1';
            cliente->residencial.telefone[2] = ' ';
            cliente->residencial.telefone[3] = '3';
            _telResidencial(cliente);
          break;
  }
}
void _telResidencial(_CLIENTE* cliente)
{
  int i;
    char num[10] = {'1','2','3','4','5','6','7','8','9','0'};
  for(i = 4; i < 7; i++){
    cliente->residencial.telefone[i] = num[rand() % 10];
   }
   cliente->residencial.telefone[7] = '-';
   for(i = 8; i < 12; i++){
     cliente->residencial.telefone[i] =  num[rand() % 10];
    }
    cliente->residencial.telefone[12] = '\0';
}

void telCelular(_CLIENTE* cliente, int Est)
{
  int i, x = 1 + ( rand() % 5 );


    cliente->celular[0].quantCelular = x;

    for(i = 0; i < x; i++){
      switch (Est) {
        case 0:
                cliente->celular[i].telefone[0] = '6';
                cliente->celular[i].telefone[1] = '7';
                cliente->celular[i].telefone[2] = ' ';
                cliente->celular[i].telefone[3] = '9';
                cliente->celular[i].telefone[4] = '9';
                _telCelular(cliente, i);
              break;
        case 1:
                cliente->celular[i].telefone[0] = '1';
                cliente->celular[i].telefone[1] = '1';
                cliente->celular[i].telefone[2] = ' ';
                cliente->celular[i].telefone[3] = '9';
                cliente->celular[i].telefone[4] = '9';
                _telCelular(cliente, i);
              break;
        case 2:
                cliente->celular[i].telefone[0] = '2';
                cliente->celular[i].telefone[1] = '1';
                cliente->celular[i].telefone[2] = ' ';
                cliente->celular[i].telefone[3] = '9';
                cliente->celular[i].telefone[4] = '9';
                _telCelular(cliente, i);
              break;
        case 3:
                cliente->celular[i].telefone[0] = '6';
                cliente->celular[i].telefone[1] = '5';
                cliente->celular[i].telefone[2] = ' ';
                cliente->celular[i].telefone[3] = '9';
                cliente->celular[i].telefone[4] = '9';
                _telCelular(cliente, i);
              break;
        case 4:
                cliente->celular[i].telefone[0] = '4';
                cliente->celular[i].telefone[1] = '1';
                cliente->celular[i].telefone[2] = ' ';
                cliente->celular[i].telefone[3] = '9';
                cliente->celular[i].telefone[4] = '9';
                _telCelular(cliente, i);
              break;
        }
   }
}
void _telCelular(_CLIENTE* cliente, int x)
{
  int i;
    char num[10] = {'1','2','3','4','5','6','7','8','9','0'};
  for(i = 5; i < 8; i++){
    cliente->celular[x].telefone[i] = num[rand() % 10];
   }
   cliente->celular[x].telefone[8] = '-';
   for(i = 9; i < 13; i++){
     cliente->celular[x].telefone[i] =  num[rand() % 10];
    }
    cliente->celular[x].telefone[13] = '\0';
}


void salario(_CLIENTE* cliente)
{
  int x = 5 + (rand() % 16);
  int y = rand() % 10;
  cliente->renda_mensal = (1000 * x) + (100 * y);
}


void exibi_CLIENTE(_CLIENTE* cliente,int inicio, int TOT_CLIENTE, int path)
{
  int j = 0,i,verifica = 0, x;

  if(!path){
    printf("\n\n=-=-=-=-=-=-=-=-=-=-=-=- \033[7mCLIENTES CADASTRADOS\033[m -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-");
  }

  for(i = inicio; i < TOT_CLIENTE; i++){

    if( cliente[i].status ){
      if(!path){
        printf("\n\n=-=-=-=-=-=-=-=- %d -=-=-=-=-=-=-=-=\n",j+ 1);
      }else{
        printf("\n\n=-=-=-=-=-=-=-=- CLIENTE INSERIDO -=-=-=-=-=-=-=-=\n");
      }
      printf("DADOS \n");
      printf("\t* Nome:     %s\n",cliente[i].nome);
      printf("\t* CPF:      %s\n", cliente[i].cpf);
      printf("\t* Salario mensal: R$ %.2f\n",cliente[i].renda_mensal);

      printf("CONTATO \n");
      printf("\t* Fixo:     - %s\n",cliente[i].residencial.telefone);
      printf("\t* Celular(es):\n");
      for(x = 0; x < cliente[i].celular[0].quantCelular; x++){
          printf("\t\t    - %s\n", cliente[i].celular[x].telefone);
      }
      printf("ENDERECO\n");
      printf("\t* Estado: %s\n",cliente[i].endereco.estado);
      printf("\t* Cidade: %s\n",cliente[i].endereco.cidade);
      printf("\t* CEP: %s\n",cliente[i].endereco.cep);
      printf("\t* Bairro: %s\n",cliente[i].endereco.bairro);
      printf("\t* Rua: %s\n",cliente[i].endereco.rua);
      printf("\t* N° %d\n",cliente[i].endereco.numero);
      verifica = 1;
      j++;
    }
  }
  if( !verifica )
      printf("\n\n\t\033[31mNenhum cliente no sistema.\033[m\n\n");
}


int excluir_CLIENTE(_CLIENTE*  cliente, int TOT_CLIENTE)
{
  _CLIENTE tmp;
  int i, verifica = 0, pos;
  char cpf[14];
  printf("\n\nInsira o CPF do cliente que sera excluido (\033[31mFORMATO:\033[m 999.999.999-99): ");
  __fpurge(stdin);
  fgets(cpf,15,stdin);

  for(i = 0; i < TOT_CLIENTE; i++){
    if( !strcmp( cpf, cliente[i].cpf ) )
    {
        verifica = 1;
        pos = i;
    }
  }

  if( verifica ){
    if(cliente[pos].status){
        tmp = cliente[TOT_CLIENTE - 1];
        cliente[TOT_CLIENTE - 1] = cliente[pos];
        cliente[pos] = tmp;
        printf("\n\n\tCliente excluido com sucesso! \n\n");
        return 1;
      }else{
        printf("\n\n\t\033[31mEste cliente não pode ser excluido pois exite uma venda em seu nome.\033[m\n\n");
      }
  }
  else{
    printf("\n\n\t\033[31mNao registro cliente para o cpf informado.\033[m\n\n");
  }
  return 0;
}

void ordena_CLIENTE(_CLIENTE* cliente,int TOT_CLIENTE)
{
  int count, i;
  _CLIENTE tmp;
  for(count = 0; count < TOT_CLIENTE; count++){
    for(i = 1 + count; i < TOT_CLIENTE; i++){
        if(strcmp(cliente[count].nome, cliente[i].nome) > 0){
          tmp = cliente[count];
          cliente[count] = cliente[i];
          cliente[i] = tmp;
        }
    }
  }
}

void ordenaNomeSalario_CLIENTE(_CLIENTE* cliente,int TOT_CLIENTE)
{
  int count, i;
  _CLIENTE tmp;
  for(count = 0; count < TOT_CLIENTE; count++){
    for(i = 1 + count; i < TOT_CLIENTE; i++){
        if(strcmp(cliente[count].nome, cliente[i].nome) > 0){
          tmp = cliente[count];
          cliente[count] = cliente[i];
          cliente[i] = tmp;
        }
    }
  }
  for(count = 0; count < TOT_CLIENTE; count++){
    for(i = 1 + count; i < TOT_CLIENTE; i++){
        if(!strcmp( cliente[count].nome, cliente[i].nome ) ){
          if( cliente[count].renda_mensal > cliente[i].renda_mensal){
            tmp = cliente[count];
            cliente[count] = cliente[i];
            cliente[i] = tmp;
          }
        }else{
          continue;
        }
    }
  }
}
