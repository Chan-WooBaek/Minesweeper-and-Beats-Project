void remove_pokemon(Pokedex pokedex) {
    // if there are no pokemons
    if (pokedex->head == NULL)
    {
        return;
    }
    Pokemon current_pokemon = get_current_pokemon(pokedex);
    Pokenode current_pokenode = pokemons_pokenode(pokedex, current_pokemon);
    Pokenode temp_pokenode = pokedex->head;
    // if there is only 1 pokemon
    if (temp_pokenode->next == NULL)
    {
        Pokenode pokenode_remove = pokedex->head;
        destroy_pokemon(pokenode_remove->pokemon);
        free(pokenode_remove);
        pokedex->head = NULL;
    }
    // if pokemon to be removed is the last in the pokedex
    else if (current_pokenode->next == NULL)
    {
        prev_pokemon(pokedex);
        while (temp_pokenode->next != current_pokenode)
        {
            temp_pokenode = temp_pokenode->next;
        }
        temp_pokenode->next = NULL;
        destroy_pokemon(current_pokenode->pokemon);
        free(current_pokenode);
    }
    else
    {
        next_pokemon(pokedex);
        if (pokedex->head == current_pokenode)
        {
            pokedex->head = current_pokenode->next;
            destroy_pokemon(current_pokenode->pokemon);
            free(current_pokenode);
        }
        else
        {
            temp_pokenode = pokedex->head;
            while (temp_pokenode->next != current_pokenode)
            {
                temp_pokenode = temp_pokenode->next;
            }
            temp_pokenode->next = current_pokenode->next;
            destroy_pokemon(current_pokenode->pokemon);
            free(current_pokenode);
        }
    }
    return;
}
