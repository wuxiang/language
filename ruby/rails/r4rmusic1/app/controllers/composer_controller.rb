class ComposerController < ApplicationController
  def show
      @work = Composer.find(params[:id]);
  end
end
