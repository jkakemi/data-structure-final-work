# data-structure-final-work
Final work of data structure doubly linked list in C.

O trabalho consiste em fazer um programa para gerenciar clientes e produtos.
O trabalho será constituido das seguintes estruturas:
• Data (dia, mês e ano);
• Endereço (rua, número, cidade, estado);
• Cliente (cpf, nome, telefone, endereço (tipo endereço), data de nascimento (tipo
data));
• Produto (código, descrição, quantidade em estoque, preço_unitário);
• Venda (CodVenda, Cpf_C(Cliente), cod_prod (Produto), qtde_comprada);
O programa deverá ter menu para:
• inclusão, alteração, consulta, deleção do cliente;
• inclusão, alteração, consulta, deleção de produto;
• inclusão, alteração, consulta, deleção de venda;
Para Cliente e Produto, o programa não deverá aceitar cpfs e códigos já cadastrados
anteriormente ;
O cliente só poderá comprar um produto, se o mesmo já estiver cadastrado;
O produto só poderá ser excluído se o mesmo, não estiver cadastrado em nenhuma venda;
O Cliente só poderá ser excluído se o mesmo, não estiver cadastrado em nenhuma venda;
Se o produto estiver com a quantidade em estoque menor que a quantidade a ser vendida, a
venda não poderá ser efetivada.
Deverá ter opções para as seguintes listagens:
• Todos os clientes cadastrados;
• Todos os produtos cadastrados;
• Todas as vendas efetivadas;
• Quantos clientes compraram acima de um determinado valor escolhido pelo usuário;
• Quais os produtos que estão com a quantidade em estoque abaixo de um
determinado valor escolhido pelo usuário;
Realizar o trabalho em lista duplamente encadeada.
