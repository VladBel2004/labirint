set number
set tabstop=3
syntax on
set hlsearch
set incsearch
set expandtab
set cursorline aleph=224
" Colorsceme spacegray, gruvbox

" Code from vim plugin-installer
call plug#begin("~/.config/nvim/plugged")
" Code for installing plugins: Plug 'tpope/vim-sensible'

Plug 'scrooloose/nerdtree'
Plug 'morhetz/gruvbox'
Plug 'Valloric/YouCompleteMe'
Plug 'jiangmiao/auto-pairs'
Plug 'kien/ctrlp.vim'
Plug 'easymotion/vim-easymotion'
Plug 'vim-airline/vim-airline'
Plug 'vim-airline/vim-airline-themes'
Plug 'mattn/emmet-vim'
Plug 'davidhalter/jedi-vim'
Plug 'python-mode/python-mode'
Plug 'majutsushi/tagbar'
Plug 'terryma/vim-multiple-cursors'
Plug 'romgrk/winteract.vim'
Plug 'tpope/vim-surround'
Plug 'scrooloose/nerdcommenter'
Plug 'jlanzarotta/bufexplorer'
" Plug '2072/PHP-Indenting-for-VIm'
" Plug 'MarcWeber/vim-addon-mw-utils' 
" Plug 'tomtom/tlib_vim' 
" Plug 'garbas/vim-snipmate'
" Plug 'honza/vim-snippets'

call plug#end()

colorscheme gruvbox
set background=dark

let g:airline_theme='wombat'

let g:mapleader='.'

let g:pymode_options = 0
let g:pymode_breakpoint = 0
let g:pymode_lint_on_write = 0
let g:pymode_lint = 1
let g:pymode_lint_message = 1
let g:pymode_folding = 0
let max_doc_height = 5

" CtrlP
let g:ctrlp_working_path_mode = 'car'

map <Leader>n :NERDTreeToggle<CR>
map <F6> <ESC>:NERDTreeToggle<CR>
nmap <F8> :TagbarToggle<CR>
nmap <F7> .bt
nmap <F5>        :InteractiveWindow<CR>
" nmap <silent>;r :PymodeRun<CR>
map <Leader> <Plug>(easymotion-prefix)

" CtrlP macros
nmap <F9> :CtrlP<CR>

