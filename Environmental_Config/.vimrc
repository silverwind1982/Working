set cindent
set autoindent
set ruler
set showmode
set shiftwidth=2
set tabstop=2
set expandtab
set incsearch
set number
set hls 
set nocompatible
set guifontset=8x16,kc15f,-*-16-*-big5-0 
set cursorline
set autoread
"set fenc=big5 enc=big5 tenc=utf8

syntax on
highlight Comment ctermfg=darkcyan
highlight Search term=reverse ctermbg=4 ctermfg=7
highlight CursorLine cterm=none ctermbg=0 
set background=dark
if has("autocmd")
   autocmd BufRead *.txt set tw=78
   autocmd BufReadPost *
      \ if line("'\"") > 0 && line ("'\"") <= line("$") |
      \   exe "normal g'\"" |
      \ endif
endif
nnoremap <F12> :TlistToggle<CR>
nnoremap <silent> <F3> :NERDTree<CR>
nnoremap <silent> <F7> :TlistOpen<CR>
nnoremap <silent> <F8> :TlistToggle<CR>
filetype plugin on

"let g:neocomplcache_enable_at_startup = 1
