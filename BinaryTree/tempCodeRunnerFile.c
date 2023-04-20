   if(tree1==NULL && tree2==NULL)
   return 1;
   if(tree1==NULL || tree2 == NULL)
    return 0;
    if(tree1->item != tree2->item)
    return 0;
    identical(tree1->left, tree2->left);
    identical(tree1->right, tree2->right);
    return 1;
