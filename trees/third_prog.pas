program third;

type
    link_t = ^tree_element_t;
    tree_element_t = record
                    body :integer;
                    left :link_t;
                    right :link_t;
                    prev :link_t;
                    end;

var
    i, mode, n, curr_level :integer;
    root :link_t;
    flag_readln :boolean;

procedure Memory_cleaning(node :link_t);

begin
    if (node^.left = nil) and (node^.right = nil) then
        dispose(node)
    else
    begin
        if node^.left <> nil then
            Memory_cleaning(node^.left);
        if node^.right <> nil then
            Memory_cleaning(node^.right);
        dispose(node);
    end;
end;

procedure Add(element :integer; var node :link_t);//Adding elements

begin
    if element < (node^.body) then
    begin
        if node^.left = nil then
        begin
            new(node^.left);
            node^.left^.prev := node;
            node^.left^.body := element;
            node^.left^.left := nil;
            node^.left^.right := nil;
        end
        else    
            Add(element, node^.left);
    end
    else
    begin
        if node^.right = nil then
        begin
            new(node^.right);
            node^.right^.prev := node;
            node^.right^.body := element;
            node^.right^.left := nil;
            node^.right^.right := nil;
        end
        else
            Add(element, node^.right);
    end;
end;

function Full_read(): integer;

var 
    element :integer;
    flag_readln :boolean;
begin
    Full_read := 0;
    repeat
        flag_readln := true;
        if eof then
            exit;
        {$I-}
        read(element);
        {$I+}
        if IOResult <> 0 then
        begin
            writeln('Some error here, please repeat enter');
            flag_readln := false;
        end
    until (flag_readln = true) or (eof);
    if not eof then
        Full_read := element;
end;

procedure Tree_entering(var root :link_t);//Tree entering

var
    element :integer;

begin
    if not eof then
        root^.body := Full_read()
    else
    begin
        writeln('Nothing to read');
        halt(1);
    end;
    root^.left := nil;
    root^.right := nil;
    root^.prev := nil;
    repeat
        element := Full_read();
        if not eof then
           Add(element, root);
    until (eof);
end;

procedure Mode_first(node :link_t);//Printing in depth

begin
    if (node^.right = nil) and (node^.left = nil) then
        writeln(node^.body)
    else 
    begin
        if node^.right <> nil then
            Mode_first(node^.right);
        writeln(node^.body);
        if node^.left <> nil then
            Mode_first(node^.left);
    end;
end;

procedure Level_curr(node :link_t; level :integer);

begin
    if level = curr_level then
        write(node^.body, ' ')
    else
    begin
        if node^.left <> nil then
            Level_curr(node^.left, level + 1);
        if node^.right <> nil then
            Level_curr(node^.right, level + 1);
    end;
end;


function Height(node :link_t): integer;

var
    h, h1, h2 :integer;

begin
    h1 := 0;
    h2 := 0;
    if (node^.left = nil) and (node^.right = nil) then
        Height := 1
    else 
    begin
        if node^.left <> nil then
            h1 := Height(node^.left);
        if node^.right <> nil then 
            h2 := Height(node^.right);
        if h1 > h2 then
            Height := h1 + 1
        else 
            Height := h2 + 1;
    end;

    
end;

procedure Mode_second(node :link_t);//BFS

begin
    for curr_level := Height(node) downto 1 do
    begin
        Level_curr(node, 1);
        writeln();
    end;
end;

function Min_branch(node :link_t):integer;

var
    min1, min2: integer;
begin
    min1 := 0;
    min2 := 0;
    if (node^.left = nil) and (node^.right = nil) then
    begin
        Min_branch := 1;
        exit;
    end;
    if node^.right <> nil then
        min1 := Min_branch(node^.right);
    if node^.left <> nil then
        min2 := Min_branch(node^.left);
    if (min1 <> 0) and (min2 <> 0) then
        if min1 < min2 then
            Min_branch := min1 + 1
        else
            Min_branch := min2 + 1
    else
        if min1 = 0 then
            Min_branch := min2 + 1
        else
            Min_branch := min1 + 1;        
end;

procedure Mode_third(node :link_t);

begin
    write(Min_branch(node), ' ');
    writeln(Height(node));
end;

procedure Nodes_in_file(var tree :text; node :link_t);

begin
    if (node^.right = nil) and (node^.left = nil) then
    begin
        writeln(tree, '    ', n, ' [label="', node^.body, '"];');
        n := n + 1;
    end
    else 
    begin
        if node^.left <> nil then
            Nodes_in_file(tree, node^.left);
        writeln(tree, '    ', n, ' [label="', node^.body, '"];');
        n := n + 1;
        if node^.right <> nil then
            Nodes_in_file(tree, node^.right);
        
        
    end;
end;

function Size_of_branch(node :link_t): integer;

begin
    Size_of_branch := 1;
    if node^.left <> nil then
        Size_of_branch := Size_of_branch + Size_of_branch(node^.left);
    if node^.right <> nil then 
        Size_of_branch := Size_of_branch + Size_of_branch(node^.right);
end;

procedure Branches_in_file(var tree :text; node :link_t; n :integer);

var 
    size :integer;
begin
    if node^.left <> nil then
    begin
        size := Size_of_branch(node^.left) + 1;
        if node^.left^.left <> nil then
            writeln(tree, '    ', size + n - 1, ' -> ', Size_of_branch(node^.left^.left) + n, '[label="L"];')
        else
            writeln(tree, '    ', size + n - 1, ' -> ', n, '[label="L"];');
        Branches_in_file(tree, node^.left, n);
    end;
    if node^.right <> nil then
    begin
        if node^.left <> nil then
            size := Size_of_branch(node^.left) + 1
        else 
            size := 1;
        if node^.right^.left <> nil then
            writeln(tree, '    ', size + n - 1, ' -> ', Size_of_branch(node^.right^.left) + size + n, '[label="R"];')
        else
            writeln(tree, '    ', size + n - 1, ' -> ', n + size, '[label="R"];');
        Branches_in_file(tree, node^.right, n + size);
    end;
end;

procedure Mode_fourth(node :link_t);

var
    tree: text;
    b :char;

begin
    n := 1;
    assign(tree, 'tree.dot');
    rewrite(tree);
    writeln(tree, 'digraph');
    writeln(tree, '{');
    Nodes_in_file(tree, node);
    writeln(tree, '//edges');
    n := 1;
    Branches_in_file(tree, node, n);
    writeln(tree, '}');
    close(tree);
    writeln('Tree in tree.dot');
end;

begin
    writeln('Modes: ');
    writeln('1: Printing in depth');
    writeln('2: Printing by levels');
    writeln('3: Print heigth of the tree and the shortest branch');
    writeln('4: Printing in .dot format');
    writeln('Please, choose a mode:');
    repeat
        flag_readln := true;
        if eof() then
        begin
            writeln('End of file');
            halt(1);
        end;
        {$I-}
        read(mode);
        {$I+}
        if IOResult <> 0 then
        begin
            writeln('Some error here, please repeat enter');
            flag_readln := false;
        end
        else if (mode < 1) or (mode > 4) then
        begin
            writeln('Please inter one of the values: 1, 2, 3, 4:');
            flag_readln := false;
        end;
    until flag_readln = true;
    readln();
    new(root);
    writeln('Please, enter values: ');
    Tree_entering(root);
    writeln('There''s the result:');
    if mode = 1 then
        Mode_first(root)
    else if mode = 2 then
        Mode_second(root)
    else if mode = 3 then
        Mode_third(root)
    else
        Mode_fourth(root);
    Memory_cleaning(root);
end.